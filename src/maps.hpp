#pragma once
#include <raylib.h>
#include "ray_tilemap.h"

namespace Maps {
    extern RayTiled::TileMap Map;

    bool  LoadMap(const char* mapPath, Camera2D& cam);
    bool  DrawMap();
    void  UnloadMap();
}
