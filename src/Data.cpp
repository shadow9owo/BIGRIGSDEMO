#include "Data.hpp"
#include "Types.h"
#include <unordered_map>
#include <raylib.h>
#include <vector>
#include <map>
#include <string>

namespace Data
{
    bool running = true;
    _Truck Player = {};
    _Truck Bot1 = {};
    _Truck Bot2 = {};
    _Truck bot3 = {};

    std::map<std::string,int> scoreleaderboard = {
        {"MAT",1000},
        {"PAT",2000},
        {"AKL",500},
        {"IRL",3000},
        {"IRE",4000},
        {"LAN",7000},
        {"PEN",5500},
        {"PAN",15000},
        {"TAU",1500}
    };

    int checkpointsc = 0;

    bool paused;

    int pbscore;

    int lap = 1;

    Vector2I windowsize = {256,240};
    Camera2D camera = {};
    Scenes currentscene = mainmenu;
   
    std::unordered_map<Texture*, Textureid> texturedict;
    std::unordered_map<Textureid, std::vector<Texture*>> tilemap;

    std::vector<Particle> particles;

    bool stop_thestopwatch = true;

    bool debug = false;

    int tick = 0;

    namespace maps
    {
        HeightMap plains;
        HeightMap city;
        HeightMap village;
        HeightMap desert;
        HeightMap forest;

        noise::module::Perlin perlinModule;
            
        void gen(HeightMap* map) {
            float scale = 0.05f;

            perlinModule.SetFrequency(1.0);
            perlinModule.SetPersistence(0.5);
            perlinModule.SetOctaveCount(6);
            perlinModule.SetLacunarity(2.0);
            perlinModule.SetSeed(map->seed);
        
            for (int y = 0; y < 255; y++) {
                for (int x = 0; x < 255; x++) {
                    float nx = x * scale;
                    float ny = y * scale;

                    float noiseVal = (float)perlinModule.GetValue(nx, ny, 0.0);

                    map->HeightMapData[y][x] = (unsigned char)((noiseVal + 1.0f) * 127.5f);
                }
            }
        }

        void generateheightmaps()
        {
            plains.seed  = 0xABCDEF00;
            city.seed    = 0x1234ABCD;
            village.seed = 0xDE00F00D;
            desert.seed  = 0x11223344; //hex
            gen(&plains);
            gen(&city);
            gen(&village);
            gen(&desert);
            gen(&forest);
            return;
        }
    }

    void resetData()
    {
        try
        {
            particles.clear();
        }
        catch(const std::exception& e)
        {

        }
        
        Data::Player = {};
        Data::Bot1 = {};
        Data::Bot2 = {};
        Data::bot3 = {};
    }
}