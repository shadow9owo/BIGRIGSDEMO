#include "maps.hpp"
#include "Data.hpp"

namespace Maps
{
    RayTiled::TileMap Map;
    Camera2D* Camera = nullptr;

    bool LoadMap(const char* mapPath, Camera2D& cam)
    {
        Camera = &cam;
        return RayTiled::LoadTileMap(mapPath, Map);
    }

    bool DrawMap()
    {
        if (Data::currentscene == mainmenu) return true;
        if (!Camera)                         return false;

        Vector2 screenCenter = {
            Data::windowsize.x * 0.5f,
            Data::windowsize.y * 0.5f
        };

        Vector2 offset = {
            screenCenter.x - Data::Player.CarPosition.x,
            screenCenter.y - Data::Player.CarPosition.y
        };

        RayTiled::DrawTileMap(Map,
                              Camera,
                              {0,0},
                              offset);

        return true;
    }

    void UnloadMap()
    {
        RayTiled::UnloadTileMap(Map);
    }
}
