#include "raylib.h"
#include "Types.h"
#include <noise/noise.h>
#include <unordered_map>
#include <vector>
#include <map>
#include <string>

namespace Data
{
    extern std::map<std::string,int> scoreleaderboard;
    extern int pbscore;

    extern  bool running;
    extern _Truck Player;
    extern _Truck Bot1;
    extern _Truck Bot2;
    extern _Truck bot3;

    extern bool stop_thestopwatch;

    extern int lap;

    extern bool paused;

    extern Vector2I windowsize;
    extern Camera2D camera;
    extern Scenes currentscene;
    
    extern std::unordered_map<Texture*, Textureid> texturedict;
    extern std::unordered_map<Textureid, std::vector<Texture*>> tilemap;

    extern float truckrotation;
    extern Vector2 CarPosition;
    extern int tick;

    extern int checkpointsc;
    extern bool debug;

    extern std::vector<Particle> particles;

    namespace maps
    {
        extern HeightMap plains;
        extern HeightMap city;
        extern HeightMap village;
        extern HeightMap desert;
        extern HeightMap forest;
        extern HeightMap village;

        extern inline void gen(HeightMap* map);

        extern void generateheightmaps();
    }
    
    extern void resetData();
}