#include "Collision.hpp"
#include <raylib.h>
#include "ray_tilemap.h"
#include "Data.hpp"
#include <vector>
#include "Logger.hpp"
#include "SceneTransitions.hpp"
#include "Timer.hpp"
#include "Input.hpp"
#include <limits>

namespace Collisions
{
    float timer = 0;
    bool won = false;
    std::vector<RayTiled::CollisionRecord> results;

    bool collides(RayTiled::TileMap &map) // timer loop
    {
        //map.get
        if (timer <= 0)
        {
            timer = 0.05f;
        }
        else
        {
            timer -= GetFrameTime();
        }
        return false;
    }

    std::vector<std::pair<Vector2,bool>> plains_checkpoints;

    int getscore()
    {
        int tmp = Input::myclamp(Timer::stopwatch_timer,1,INT32_MAX,false);
        tmp = tmp * 100;
        tmp = 50000 - tmp;
        return tmp;
    }

    void check()
    {
        bool isendunlocked = true;
        switch (Data::currentscene)
        {
            case Racemap_plains:
            
                for (auto &entry : plains_checkpoints)
                {
                    if (Vector2Distance(entry.first, Data::Player.CarPosition) < 30)
                    {
                        if (!entry.second)
                        {
                            entry.second = true;
                            Logger::AddToLoggerBuffer("checkpoint hit");
                        }
                    }
                }
                for (auto &entry : plains_checkpoints)
                {
                    if (!entry.second)
                    {
                        isendunlocked = false;
                        break;
                    }
                }
                if (isendunlocked)
                {
                    if (Vector2Distance({88,201}, Data::Player.CarPosition) < 30)
                    {
                        if (Data::lap == 3)
                        {
                            if (Data::pbscore < getscore())
                            {
                                Data::pbscore = getscore();
                            }
                            SceneTransition::changescene(Scenes::mainmenu, 2.5f, true);
                            won = true;
                            return;
                        }
                        else
                        {
                            Data::lap++;
                            reset();
                            Logger::AddToLoggerBuffer("lap finished");
                        }
                    }
                }
                break;

            default:
                break;
        }
        return;
    }

    void reset()
    {
        plains_checkpoints.clear();

        plains_checkpoints.emplace_back(Vector2{ -292,  187 }, false);
        plains_checkpoints.emplace_back(Vector2{ -1442, -188 }, false);
        plains_checkpoints.emplace_back(Vector2{ -174,  -320 }, false);
        plains_checkpoints.emplace_back(Vector2{  88,   201 }, false);
    }
}
