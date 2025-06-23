/**********************************************************************************************
*
*   RayTileMap
*
*   LICENSE: MIT
*
*   Copyright (c) 2024 Jeffery Myers
*
*   Permission is hereby granted, free of charge, to any person obtaining a copy
*   of this software and associated documentation files (the "Software"), to deal
*   in the Software without restriction, including without limitation the rights
*   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*   copies of the Software, and to permit persons to whom the Software is
*   furnished to do so, subject to the following conditions:
*
*   The above copyright notice and this permission notice shall be included in all
*   copies or substantial portions of the Software.
*
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*   SOFTWARE.
*
**********************************************************************************************/

#include "Data.hpp"
#include "ray_tilemap.h"
#include "pugixml.hpp"

namespace RayTiled
{
    Texture2D GetTexture(const std::string& fileName);

    void TileSheet::DrawTile(uint16_t id, Rectangle destinationRectangle, uint8_t flags, Color tint) const
    {
        Rectangle sourceRect = Tiles[id - StartingTileId];
        float rotation = 0;

        if (flags & TileFlagsFlipDiagonal)
            rotation -= 90;
        if (flags & TileFlagsFlipHorizontal)
            sourceRect.width *= -1;
        if (flags & TileFlagsFlipVertical)
            sourceRect.height *= -1;

        DrawTexturePro(Texture, sourceRect, destinationRectangle, Vector2Zero(), rotation, tint);
    }

    const TileSheet* FindSheetForId(uint16_t id, const TileMap& map)
    {
        for (std::map<uint16_t, TileSheet>::const_iterator it = map.TileSheets.begin(); it != map.TileSheets.end(); ++it)
        {
            const TileSheet& sheet = it->second;
            if (sheet.HasId(id))
                return &sheet;
        }
        return nullptr;
    }


    static size_t TilesDrawn = 0;

    size_t GetTileDrawStats()
    {
        return TilesDrawn;
    }

    void DrawTileLayer(TileMap& map, TileLayer* tileLayer, Camera2D* camera, Vector2 bounds, Vector2 offset)
    {
        int startX = 0;
        int startY = 0;
    
        int endX = int(tileLayer->Bounds.x);
        int endY = int(tileLayer->Bounds.y);
    
        int xDirection = 1;
        int yDirection = 1;
    
        int layerW = int(tileLayer->Bounds.x);
        int layerH = int(tileLayer->Bounds.y);

        if (camera)
        {
            if (bounds.x <= 0 || bounds.y <= 0)
                bounds = { float(GetScreenWidth()), float(GetScreenHeight()) };
        
            Vector2 viewportStart = GetScreenToWorld2D({0,0}, *camera);
            Vector2 viewportEnd   = GetScreenToWorld2D(bounds, *camera);

            int startX = 0, startY = 0;
            int endX   = layerW  - 1;
            int endY   = layerH - 1;

        }
    
        for (int y = startY; y != endY; y += yDirection)
        {
            for (int x = startX; x != endX; x += xDirection)
            {
                Rectangle destRect;
                const auto* tile = tileLayer->GetTile(x, y, destRect);
                if (tile == nullptr || tile->TileIndex == 0)
                    continue;

                destRect.x -= offset.x;
                destRect.y -= offset.y;
            
                if (map.LastTileSheet == nullptr || !map.LastTileSheet->HasId(tile->TileIndex))
                    map.LastTileSheet = FindSheetForId(tile->TileIndex, map);
            
                if (!map.LastTileSheet)
                    continue;
            
                map.LastTileSheet->DrawTile(tile->TileIndex, destRect, tile->TileFlags, WHITE);
                TilesDrawn++;
            }
        
            if (tileLayer->CustomDrawalbeFunction)
            {
                for (auto& drawable : tileLayer->Drawables)
                {
                    float yPos = drawable->GetY();
                    if (yPos > y * tileLayer->TileSize.y && yPos <= (y + 1) * tileLayer->TileSize.y)
                        tileLayer->CustomDrawalbeFunction(*tileLayer, *drawable, startX * tileLayer->TileSize.x, endX * tileLayer->TileSize.x);
                }
            }
        }
    }
    
    void DrawVirtualLayer(TileMap& map, UserLayer* virtualLayer, Camera2D* camera, Vector2 bounds)
    {
        if (virtualLayer && virtualLayer->DrawFunction)
            virtualLayer->DrawFunction(*virtualLayer, camera, bounds);
    }

    void DrawTileMap(TileMap& map, Camera2D* camera, Vector2 bounds, Vector2 offset)
    {
        TilesDrawn = 0;
        for (auto& layer : map.Layers)
        {
            switch (layer->Type)
            {
            default:
                break;
            case TileLayerType::Tile:
                if (Data::currentscene == Scenes::Racemap_plains) //hook debug
                {
                    if (layer.get()->LayerId == 3 && !Data::debug)
                    {
                        break;
                    }
                }
                DrawTileLayer(map, static_cast<TileLayer*>(layer.get()), camera, bounds, offset);
                break;
            case TileLayerType::Object:
            {
                auto objectLayer = static_cast<ObjectLayer*>(layer.get());
                if (objectLayer && objectLayer->DrawFunc)
                    objectLayer->DrawFunc(*objectLayer, camera, bounds);
            }
            break;
            case TileLayerType::User:
                DrawVirtualLayer(map, static_cast<UserLayer*>(layer.get()), camera, bounds);
                break;
            }
        }
    }
}