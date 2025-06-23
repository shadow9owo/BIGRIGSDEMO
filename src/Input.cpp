#include "Input.hpp"
#include <raylib.h>
#include "Data.hpp"
#include <cmath>
#include "Types.h"
#include "Sounds.hpp"
#include <limits.h>
#include "SceneTransitions.hpp"

namespace Input
{

    double myclamp(double input,double min,double max,bool invert)
    {
        if (invert)
        {
            if (input < min)
            {
                return max;
            }else if (input > max)
            {
                return min;
            }else {
                return input;
            }
        }else 
        {
            if (input < min)
            {
                return min;
            }else if (input > max)
            {
                return max;
            }else {
                return input;
            }
        }
    }

            
    float maxSpeed = 5.0f;
    const float maxReverseSpeed = -3.0f;
    const float baseTurnSpeed = 2.0f;
    const float turnSpeedMultiplier = 4.0f;
    bool b = false;

    void ListenForInput()
    {
        if (Data::currentscene == mainmenu) {return;}

        if (!Data::paused)
        {
            if (!SceneTransition::transitioning)
            {
                if (Data::tick % 6 == 0)
                {
                    if (IsKeyDown(KEY_S))
                    {
                        Data::Player.acceleration = myclamp(Data::Player.acceleration - 1, maxReverseSpeed, maxSpeed, false);
                    }
                    if (IsKeyDown(KEY_W))
                    {
                        Data::Player.acceleration = myclamp(Data::Player.acceleration + 2, maxReverseSpeed, maxSpeed, false);
                    }
                    if (!(IsKeyDown(KEY_S) || IsKeyDown(KEY_W)))
                    {
                        if (Data::Player.acceleration < 0)
                        {
                            Data::Player.acceleration = myclamp(Data::Player.acceleration + 2, 0, maxSpeed, false);
                        }
                        else if (Data::Player.acceleration > 0)
                        {
                            Data::Player.acceleration = myclamp(Data::Player.acceleration - 2, 0, maxSpeed, false);
                        }
                    }
                }
            
                float speedFactor = fabs(Data::Player.acceleration) / maxSpeed;
                if (speedFactor > 1.0f) speedFactor = 1.0f;
            
                if (IsKeyDown(KEY_A))
                {
                    float turnAmount = baseTurnSpeed + (turnSpeedMultiplier * speedFactor * baseTurnSpeed);
                    Data::Player.truckrotation -= turnAmount * myclamp(Data::Player.acceleration, -1, 1, false);
                }
                if (IsKeyDown(KEY_D))
                {
                    float turnAmount = baseTurnSpeed + (turnSpeedMultiplier * speedFactor * baseTurnSpeed);
                    Data::Player.truckrotation += turnAmount * myclamp(Data::Player.acceleration, -1, 1, false);
                }
            
                if (IsKeyPressed(KEY_G))
                {
                    PlaySound(sounds::Sound_Horn);
                }
                float rad = Data::Player.truckrotation * DEG2RAD;
                float move = Data::Player.acceleration;
            
                if (move < 0.0f)
                {
                    Data::Player.CarPosition.x += cosf(rad) * move;
                    Data::Player.CarPosition.y += sinf(rad) * move;
                }
                else
                {
                    Data::Player.CarPosition.x += cosf(rad) * move;
                    Data::Player.CarPosition.y += sinf(rad) * move;
                }
            }
        }
    
        if (IsKeyPressed(KEY_F3))
        {
            Data::debug = !Data::debug;
        }

        if (IsKeyPressed(KEY_ESCAPE))
        {
            Data::paused = !Data::paused;
        }

        if (IsKeyDown(KEY_LEFT_SHIFT)) 
        {
            if (!b) {
                b = true;
                PlaySound(sounds::Sound_Boost);
            }else {
                if (!IsSoundPlaying(sounds::Sound_Boost))
                {
                    PlaySound(sounds::Sound_Boost);
                }
            }
            maxSpeed = 7.5f;
        }else {
            b = false;
            maxSpeed = 5.0f;
        }
    }   
}