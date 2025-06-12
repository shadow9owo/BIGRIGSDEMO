#include <raylib.h>
#include "ray_tilemap.h"
#include "Data.hpp"
#include <vector>

namespace Collisions
{
    extern bool won;
    extern std::vector<std::pair<Vector2,bool>> plains_checkpoints;
    extern bool collides(RayTiled::TileMap &map);
    extern void check();
    extern void reset();
}