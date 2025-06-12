#include <string.h>
#include <stdio.h>
#include <iostream>
#include <raylib.h>
#include <vector>
#include "Types.h"
#include "Data.hpp"
#include "texturemanager.hpp"
#include "Logger.hpp"

namespace Textures {
    namespace Utils {

        Texture* GrabTexture(Textureid id) {
            for (auto& pair : Data::texturedict) {
                if (pair.second == id) {
                    return pair.first;
                }
            }
            return nullptr;
        }

        Texture* GrabTileTexture(Textureid id, int index) {
            if (Data::tilemap.count(id) == 0) return nullptr;
            auto& vec = Data::tilemap[id];
            if (index < 0 || index >= static_cast<int>(vec.size())) return nullptr;
            return vec[index];
        }

        bool UnloadAll() {
            for (auto& pair : Data::texturedict) {
                Texture* ptr = pair.first;
                if (ptr) {
                    UnloadTexture(*ptr);
                    delete ptr;
                }
            }
            Data::texturedict.clear();

            for (auto& [id, tileVec] : Data::tilemap) {
                for (Texture* tile : tileVec) {
                    if (tile) {
                        UnloadTexture(*tile);
                        delete tile;
                    }
                }
            }
            Data::tilemap.clear();

            return true;
        }

        bool IsIdLoaded(Textureid id) {
            for (auto& pair : Data::texturedict) {
                if (pair.second == id) {
                    return true;
                }
            }
            return Data::tilemap.count(id) > 0;
        }

        bool LoadAllInScene(Scenes scene) {
            return true;
        }

        Texture BuildBigTextureFromTiles(Textureid id) { //works only with 48s useless !!!do not reuse
            const int tileSize = 8;
            const int tilesPerRow = 6;
            const int totalTiles = 36;
                
            if (Data::tilemap.count(id) == 0) return {};
                
            auto& tiles = Data::tilemap[id];
            Image bigImage = GenImageColor(tileSize * tilesPerRow, tileSize * (totalTiles / tilesPerRow), BLANK);
                
            for (int i = 0; i < totalTiles && i < (int)tiles.size(); ++i) {
                Texture* tileTex = tiles[i];
                if (!tileTex) continue;
            
                Image tileImg = LoadImageFromTexture(*tileTex);
                int x = (i % tilesPerRow) * tileSize;
                int y = (i / tilesPerRow) * tileSize;
            
                for (int py = 0; py < tileSize; ++py) {
                    for (int px = 0; px < tileSize; ++px) {
                        Color c = GetImageColor(tileImg, px, py);
                        ImageDrawPixel(&bigImage, x + px, y + py, c);
                    }
                }
            
                UnloadImage(tileImg);
            }
        
            Texture bigTexture = LoadTextureFromImage(bigImage);
            UnloadImage(bigImage);
            
            return bigTexture;
        }
        

        void LoadTextureById(Textureid id) {
            if (IsIdLoaded(id)) return;

            Texture2D text2dspritesheet;
            text2dspritesheet = LoadTexture("./assets/tilesforplains.png");

            switch (id) {
                case Truck: {
                    const int tileCount = 36;
                    std::vector<Texture*> tiles;

                    for (int i = 0; i < tileCount; ++i) {
                        char path[64];
                        snprintf(path, sizeof(path), "./assets/truck_1_%d.png", i);

                        if (!FileExists(path)) continue;

                        Image img = LoadImage(path);
                        Texture* tile = new Texture(LoadTextureFromImage(img));
                        UnloadImage(img);
                        tiles.push_back(tile);
                    }

                    Data::tilemap[id] = tiles;

                    Texture bigTex = BuildBigTextureFromTiles(id);
                    Texture* bigTexPtr = new Texture(bigTex);
                    Data::texturedict[bigTexPtr] = id;

                    break;
                }
                case Collision:
                {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/collision.png");
                    Data::texturedict.insert({ tmppoint, id }); 
                }
                case Winner:
                {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/winner.png");
                    Data::texturedict.insert({ tmppoint, id }); 
                }
                case PLAINS_Plain_empty: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/tilesetforplains.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case PLAINS_Road_0deg: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/tilesetforplains.png");
                    Data::texturedict.insert({ tmppoint, id }); 
                    break;
                }
                case PLAINS_Road_Turn: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/tilesetforplains.png");
                    Data::texturedict.insert({ tmppoint, id }); 
                    break;
                }
                case PLAINS_Road_90deg: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/tilesetforplains.png");
                    Data::texturedict.insert({ tmppoint, id }); 
                    break;
                }
                case PLAINS_Plain_Grass: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/tilesetforplains.png");
                    Data::texturedict.insert({ tmppoint, id }); 
                    break;
                }
                case PLAINS_Treetop: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/tilesetforplains.png");
                    Data::texturedict.insert({ tmppoint, id }); 
                    break;
                }
                case PLAINS_Treebot: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/tilesetforplains.png");
                    Data::texturedict.insert({ tmppoint, id }); 
                    break;
                }
                case PLAINS_Tree2top: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/tilesetforplains.png");
                    Data::texturedict.insert({ tmppoint, id }); 
                    break;
                }
                case PLAINS_Tree2bot: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/tilesetforplains.png");
                    Data::texturedict.insert({ tmppoint, id }); 
                    break;
                }
                case UI_CORNER_FILLED: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case UI_FILLED_LINE: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case UI_BG_FILLED: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case UI_CORNER_EMPTY_BR: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case UI_CORNER_ROUND_EMPTY_1: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case UI_CORNER_ROUND_EMPTY_2: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case UI_VERT_EMPTY: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case UI_VERT_END: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case UI_SLAB: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case UI_HORIZONTAL: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case UI_SHARP_EDGE: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case UI_SHORT_BLOCKY_TURN: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case UI_CORNER_BLOCKY2: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case FONT_LETTER_R: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case FONT_LETTER_S: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case FONT_LETTER_1: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case FONT_LETTER_Q: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case FONT_LETTER_T: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case FONT_LETTER_2: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case FONT_LETTER_P: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case FONT_LETTER_U: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case FONT_LETTER_3: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case FONT_LETTER_N: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case FONT_LETTER_O: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case FONT_LETTER_V: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case FONT_LETTER_4: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case FONT_LETTER_F: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case FONT_LETTER_M: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case FONT_LETTER_W: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case FONT_LETTER_5: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case FONT_LETTER_C: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case FONT_LETTER_E: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case FONT_LETTER_G: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case FONT_LETTER_L: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case FONT_LETTER_X: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case FONT_LETTER_6: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case FONT_LETTER_A: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case FONT_LETTER_H: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case FONT_LETTER_K: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case FONT_LETTER_Y: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case FONT_LETTER_7: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case FONT_LETTER_B: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case FONT_LETTER_D: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case FONT_LETTER_I: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case FONT_LETTER_J: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case FONT_LETTER_Z: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case FONT_LETTER_8: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case FONT_LETTER_9: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
                case FONT_LETTER_0: {
                    Texture2D* tmppoint = new Texture2D();
                    *tmppoint = LoadTexture("./assets/uiset.png");
                    Data::texturedict.insert({ tmppoint, id });
                    break;
                }
            
            UnloadTexture(text2dspritesheet);
        }
        }

        bool LoadAll() {
            for (size_t i = 0; i < 64; i++)
            {
                try
                {
                    LoadTextureById(static_cast<Textureid>(i));
                }
                catch(const std::exception& e)
                {
                    Logger::AddToLoggerBuffer(e.what());
                }
                
            }
            return true;
        }
        

        Rectangle GrabRectangle(Textureid id) //please end my suffering
        {
            switch (id)
            {
                case PLAINS_Plain_empty:
                    return {8,0,8,8};
                case PLAINS_Plain_Grass:
                    return {0,0,8,8};
                case PLAINS_Road_0deg:
                    return {16,0,8,8};
                case PLAINS_Road_90deg:
                    return {24,8,8,8};
                case PLAINS_Road_Turn:
                    return {16,8,8,8};
                case PLAINS_Tree2bot:
                    return {32,32,8,8};
                case PLAINS_Tree2top:
                    return {32,24,8,8};
                case PLAINS_Treebot:
                    return {24,32,8,8};
                case PLAINS_Treetop:
                    return {24,24,8,8};
                case UI_CORNER_FILLED:
                    return {0,0,8,8};
                case UI_FILLED_LINE:
                    return {8,0,8,8};
                case UI_BG_FILLED:
                    return {16,0,8,8};
                case UI_CORNER_EMPTY_BR:
                    return {16,8,8,8};
                case UI_CORNER_ROUND_EMPTY_1:
                    return {0,8,8,8};
                case UI_CORNER_ROUND_EMPTY_2:
                    return {8,8,8,8};
                case UI_VERT_EMPTY:
                    return {0,16,8,8};
                case UI_VERT_END:
                    return {0,24,8,8};
                case UI_SLAB:
                    return {8,24,8,8};
                case UI_HORIZONTAL:
                    return {8,16,8,8};
                case UI_SHARP_EDGE:
                    return {16,8,8,8};
                case UI_SHORT_BLOCKY_TURN:
                    return {0,32,8,8};
                case UI_CORNER_BLOCKY2:
                    return {8,32,8,8};
                case FONT_LETTER_R:
                    return {24,0,8,8};
                case FONT_LETTER_S:
                    return {32,0,8,8};
                case FONT_LETTER_1:
                    return {40,0,8,8};
                case FONT_LETTER_Q:
                    return {24,8,8,8};
                case FONT_LETTER_T:
                    return {32,8,8,8};
                case FONT_LETTER_2:
                    return {40,8,8,8};
                case FONT_LETTER_P:
                    return {24,16,8,8};
                case FONT_LETTER_U:
                    return {32,16,8,8};
                case FONT_LETTER_3:
                    return {40,16,8,8};
                case FONT_LETTER_N:
                    return {16,24,8,8};
                case FONT_LETTER_O:
                    return {24,24,8,8};
                case FONT_LETTER_V:
                    return {32,24,8,8};
                case FONT_LETTER_4:
                    return {40,24,8,8};
                case FONT_LETTER_F:
                    return {16,32,8,8};
                case FONT_LETTER_M:
                    return {24,32,8,8};
                case FONT_LETTER_W:
                    return {32,32,8,8};
                case FONT_LETTER_5:
                    return {40,32,8,8};
                case FONT_LETTER_C:
                    return {8,48,8,8};
                case FONT_LETTER_E:
                    return {8,40,8,8};
                case FONT_LETTER_G:
                    return {16,40,8,8};
                case FONT_LETTER_L:
                    return {24,40,8,8};
                case FONT_LETTER_X:
                    return {32,40,8,8};
                case FONT_LETTER_6:
                    return {40,40,8,8};
                case FONT_LETTER_A:
                    return {0,48,8,8};
                case FONT_LETTER_H:
                    return {16,48,8,8};
                case FONT_LETTER_K:
                    return {24,48,8,8};
                case FONT_LETTER_Y:
                    return {32,48,8,8};
                case FONT_LETTER_7:
                    return {40,48,8,8};
                case FONT_LETTER_B:
                    return {0,56,8,8};
                case FONT_LETTER_D:
                    return {8,56,8,8};
                case FONT_LETTER_I:
                    return {16,56,8,8};
                case FONT_LETTER_J:
                    return {24,56,8,8};
                case FONT_LETTER_Z:
                    return {32,56,8,8};
                case FONT_LETTER_8:
                    return {40,56,8,8};
                case FONT_LETTER_9:
                    return {48,0,8,8};
                case FONT_LETTER_0:
                    return {48,8,8,8};
                default:
                    return {};  
            }
            return {};
        }
    }

    int availiblevramMBs() {
        return 256;
    }

    bool _LoadTextures() {
        if (availiblevramMBs() < 128) {
            Utils::LoadAllInScene(Data::currentscene);
        } else {
            Utils::LoadAll();
        }

        return true;
    }
}
