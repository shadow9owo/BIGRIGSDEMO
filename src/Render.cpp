#include "Data.hpp"
#include "Types.h"
#include "Render.hpp"
#include "texturemanager.hpp"
#include <iostream>
#include <math.h>
#include <string>
#include <raylib.h>
#include "Input.hpp"
#include "Debug.hpp"
#include <algorithm>
#include <vector>
#include "maps.hpp"
#include "Timer.hpp"
#include "Collision.hpp"
#include "SceneTransitions.hpp"

namespace Render
{
    namespace Utils
    {
        namespace Particles
        {
            bool RenderParticles()
            {
                for (Particle i : Data::particles)
                {
                    if (i.texture)
                    {
                        Texture2D txt = *Textures::Utils::GrabTexture((Textureid)i.texture);
                        DrawTexturePro(txt,Textures::Utils::GrabRectangle((Textureid)i.texture),{i.sizepos.x,i.sizepos.y,i.sizepos.width,i.sizepos.height},{0,0},i.rotation,i.color);
                    }else {
                        DrawRectanglePro(i.sizepos,{0,0},i.rotation,i.color);
                    }
                }
                return true;
            }
            void ParticlePhysics() //loops
            {
                if (Data::tick % 4 == 0)
                {
                    for (Particle i : Data::particles)
                    {
                        i.sizepos = 
                        {
                            i.sizepos.x,
                            i.sizepos.y + (GetRandomValue(-3,-1)),
                            i.sizepos.width,
                            i.sizepos.height
                        };

                        if (i.sizepos.y > Data::windowsize.y)
                        {
                            i.sizepos = 
                            {
                                i.sizepos.x,
                                0,
                                i.sizepos.width,
                                i.sizepos.height
                            };
                        }

                        i.rotation = i.rotation + Input::myclamp(GetRandomValue(-5,5),0,360,true);
                    }
                }
                return;
            }
        }
        namespace UI
        {
            void DrawWindow()
            {
                return;
            }

            Rectangle GetTextLenght(std::string content,float scale)
            {
                Rectangle tmp = {};
                float scalex = (float)GetMonitorWidth(0) / (float)Data::windowsize.x;
                float scaley = (float)GetMonitorHeight(0) / (float)Data::windowsize.y;
                for (char c : content)
                {
                    if (c == '\n')
                    {
                        tmp.height = tmp.y + 8 * scale;
                    }
                    else 
                    {
                        tmp.width = tmp.x = 8 * scale;
                    }
                }

                return {0,0,tmp.width,tmp.height};
            }

            void DrawText(std::string content, Rectangle textloc, float scale = 1.0f, Color color = Color{ 255, 255, 255, 255 })
            {
                float newline = textloc.y;
                float x = textloc.x;

                for (char c : content)
                {
                    switch (tolower(c))
                    {
                            case 'a':
                            {
                                DrawTexturePro(*Textures::Utils::GrabTexture(Textureid::FONT_LETTER_A),
                                    Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_A),
                                    Rectangle{ x, newline,
                                               Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_A).width * scale,
                                               Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_A).height * scale },
                                    Vector2{ 0, 0 }, 0.0f, color);

                                x = x + 8 * scale;
                                break;
                            }
                            case 'b':
                            {
                                DrawTexturePro(*Textures::Utils::GrabTexture(Textureid::FONT_LETTER_B),
                                    Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_B),
                                    Rectangle{ x, newline,
                                               Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_B).width * scale,
                                               Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_B).height * scale },
                                    Vector2{ 0, 0 }, 0.0f, color);
                                x = x + 8 * scale;
                                break;
                            }
                            case 'c':
                            {
                                DrawTexturePro(
                                    *Textures::Utils::GrabTexture(Textureid::FONT_LETTER_C),
                                    Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_C),
                                    Rectangle{ x, newline,
                                               Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_C).width * scale,
                                               Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_C).height * scale },
                                    Vector2{ 0.0f, 0.0f },
                                    0.0f,
                                    color
                                );
                                x = x + 8 * scale;
                                break;
                            }
                            case 'd':
                            {
                                DrawTexturePro(*Textures::Utils::GrabTexture(Textureid::FONT_LETTER_D),
                                    Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_D),
                                    Rectangle{ x, newline,
                                               Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_D).width * scale,
                                               Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_D).height * scale },
                                    Vector2{ 0.0f, 0.0f }, 0.0f, color);

                                x = x + 8 * scale;
                                break;
                            }
                            case 'e':
                            {
                                DrawTexturePro(*Textures::Utils::GrabTexture(Textureid::FONT_LETTER_E),
                                    Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_E),
                                    Rectangle{ x, newline,
                                               Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_E).width * scale,
                                               Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_E).height * scale },
                                    Vector2{ 0.0f, 0.0f }, 0.0f, color);

                                x = x + 8 * scale;
                                break;
                            }
                            case 'f':
                            {
                                DrawTexturePro(*Textures::Utils::GrabTexture(Textureid::FONT_LETTER_F),
                                    Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_F),
                                    Rectangle{ x, newline,
                                               Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_F).width * scale,
                                               Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_F).height * scale },
                                    Vector2{ 0.0f, 0.0f }, 0.0f, color);

                                x = x + 8 * scale;
                                break;
                            }
                            case 'g':
                            {
                                DrawTexturePro(*Textures::Utils::GrabTexture(Textureid::FONT_LETTER_G),
                                    Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_G),
                                    Rectangle{ x, newline,
                                               Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_G).width * scale,
                                               Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_G).height * scale },
                                    Vector2{ 0.0f, 0.0f }, 0.0f, color);

                                x = x + 8 * scale;
                                break;
                            }
                            case 'h':
                            {
                                DrawTexturePro(*Textures::Utils::GrabTexture(Textureid::FONT_LETTER_H),
                                    Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_H),
                                    Rectangle{ x, newline,
                                               Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_H).width * scale,
                                               Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_H).height * scale },
                                    Vector2{ 0.0f, 0.0f }, 0.0f, color);

                                x = x + 8 * scale;

                                break;
                            }
                            case 'i':
                            {
                                DrawTexturePro(*Textures::Utils::GrabTexture(Textureid::FONT_LETTER_I),
                                    Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_I),
                                    Rectangle{ x, newline, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_I).width * scale, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_I).height * scale },
                                    Vector2{ 0.0f, 0.0f }, 0.0f, color);
                                x = x + 8 * scale;

                                break;
                            }
                            case 'j':
                            {
                                DrawTexturePro(*Textures::Utils::GrabTexture(Textureid::FONT_LETTER_J),
                                    Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_J),
                                    Rectangle{ x, newline, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_J).width * scale, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_J).height * scale },
                                    Vector2{ 0.0f, 0.0f }, 0.0f, color);
                                x = x + 8 * scale;

                                break;
                            }
                            case 'k':
                            {
                                DrawTexturePro(*Textures::Utils::GrabTexture(Textureid::FONT_LETTER_K),
                                    Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_K),
                                    Rectangle{ x, newline, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_K).width * scale, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_K).height * scale },
                                    Vector2{ 0.0f, 0.0f }, 0.0f, color);
                                x = x + 8 * scale;

                                break;
                            }
                            case 'l':
                            {
                                DrawTexturePro(*Textures::Utils::GrabTexture(Textureid::FONT_LETTER_L),
                                    Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_L),
                                    Rectangle{ x, newline, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_L).width * scale, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_L).height * scale },
                                    Vector2{ 0.0f, 0.0f }, 0.0f, color);
                                x = x + 8 * scale;

                                break;
                            }
                            case 'm':
                            {
                                DrawTexturePro(*Textures::Utils::GrabTexture(Textureid::FONT_LETTER_M),
                                    Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_M),
                                    Rectangle{ x, newline, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_M).width * scale, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_M).height * scale },
                                    Vector2{ 0.0f, 0.0f }, 0.0f, color);
                                x = x + 8 * scale;

                                break;
                            }
                            case 'n':
                            {
                                DrawTexturePro(*Textures::Utils::GrabTexture(Textureid::FONT_LETTER_N),
                                    Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_N),
                                    Rectangle{ x, newline, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_N).width * scale, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_N).height * scale },
                                    Vector2{ 0.0f, 0.0f }, 0.0f, color);
                                x = x + 8 * scale;

                                break;
                            }
                            case 'o':
                            {
                                DrawTexturePro(*Textures::Utils::GrabTexture(Textureid::FONT_LETTER_O),
                                    Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_O),
                                    Rectangle{ x, newline, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_O).width * scale, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_O).height * scale },
                                    Vector2{ 0, 0 }, 0.0f, color);
                                x = x + 8 * scale;

                                break;
                            }
                            case 'p':
                            {
                                DrawTexturePro(*Textures::Utils::GrabTexture(Textureid::FONT_LETTER_P),
                                    Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_P),
                                    Rectangle{ x, newline, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_P).width * scale, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_P).height * scale },
                                    Vector2{ 0, 0 }, 0.0f, color);
                                x = x + 8 * scale;

                                break;
                            }
                            case 'q':
                            {
                                DrawTexturePro(*Textures::Utils::GrabTexture(Textureid::FONT_LETTER_Q),
                                    Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_Q),
                                    Rectangle{ x, newline, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_Q).width * scale, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_Q).height * scale },
                                    Vector2{ 0, 0 }, 0.0f, color);
                                x = x + 8 * scale;

                                break;
                            }
                            case 'r':
                            {
                                DrawTexturePro(*Textures::Utils::GrabTexture(Textureid::FONT_LETTER_R),
                                    Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_R),
                                    Rectangle{ x, newline, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_R).width * scale, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_R).height * scale },
                                    Vector2{ 0, 0 }, 0.0f, color);
                                x = x + 8 * scale;

                                break;
                            }
                            case 's':
                            {
                                DrawTexturePro(*Textures::Utils::GrabTexture(Textureid::FONT_LETTER_S),
                                    Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_S),
                                    Rectangle{ x, newline, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_S).width * scale, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_S).height * scale },
                                    Vector2{ 0, 0 }, 0.0f, color);
                                x = x + 8 * scale;

                                break;
                            }
                            case 't':
                            {
                                DrawTexturePro(*Textures::Utils::GrabTexture(Textureid::FONT_LETTER_T),
                                    Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_T),
                                    Rectangle{ x, newline, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_T).width * scale, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_T).height * scale },
                                    Vector2{ 0, 0 }, 0.0f, color);
                                x = x + 8 * scale;

                            break;
                        }
                        case 'u':
                        {
                            DrawTexturePro(*Textures::Utils::GrabTexture(Textureid::FONT_LETTER_T),
                                Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_T),
                                Rectangle{ x, newline, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_T).width * scale, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_T).height * scale },
                                Vector2{ 0, 0 }, 0.0f, color);
                            x = x + 8 * scale;

                            break;
                        }
                        case 'v':
                        {
                            DrawTexturePro(*Textures::Utils::GrabTexture(Textureid::FONT_LETTER_V),
                                Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_V),
                                Rectangle{ x, newline, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_V).width * scale, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_V).height * scale },
                                Vector2{ 0, 0 }, 0.0f, color);
                            x = x + 8 * scale;

                            break;
                        }
                        case 'w':
                        {
                            DrawTexturePro(*Textures::Utils::GrabTexture(Textureid::FONT_LETTER_W),
                                Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_W),
                                Rectangle{ x, newline, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_W).width * scale, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_W).height * scale },
                                Vector2{ 0, 0 }, 0.0f, color);
                            x = x + 8 * scale;

                            break;
                        }
                        case 'x':
                        {
                            DrawTexturePro(*Textures::Utils::GrabTexture(Textureid::FONT_LETTER_X),
                                Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_X),
                                Rectangle{ x, newline, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_X).width * scale, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_X).height * scale },
                                Vector2{ 0, 0 }, 0.0f, color);
                            x = x + 8 * scale;

                            break;
                        }
                        case 'y':
                        {
                            DrawTexturePro(*Textures::Utils::GrabTexture(Textureid::FONT_LETTER_Y),
                                Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_Y),
                                Rectangle{ x, newline, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_Y).width * scale, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_Y).height * scale },
                                Vector2{ 0, 0 }, 0.0f, color);
                            x = x + 8 * scale;

                            break;
                        }
                        case 'z':
                        {
                            DrawTexturePro(*Textures::Utils::GrabTexture(Textureid::FONT_LETTER_Z),
                                Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_Z),
                                Rectangle{ x, newline, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_Z).width * scale, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_Z).height * scale },
                                Vector2{ 0, 0 }, 0.0f, color);
                            x = x + 8 * scale;

                            break;
                        }
                        case '0':
                        {
                            DrawTexturePro(*Textures::Utils::GrabTexture(Textureid::FONT_LETTER_0),
                                Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_0),
                                Rectangle{ x, newline, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_0).width * scale, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_0).height * scale },
                                Vector2{ 0, 0 }, 0.0f, color);
                            x = x + 8 * scale;

                            break;
                        }
                        case '1':
                        {
                            DrawTexturePro(*Textures::Utils::GrabTexture(Textureid::FONT_LETTER_1),
                                Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_1),
                                Rectangle{ x, newline, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_1).width * scale, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_1).height * scale },
                                Vector2{ 0, 0 }, 0.0f, color);
                            x = x + 8 * scale;

                            break;
                        }
                        case '2':
                        {
                            DrawTexturePro(*Textures::Utils::GrabTexture(Textureid::FONT_LETTER_2),
                                Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_2),
                                Rectangle{ x, newline, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_2).width * scale, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_2).height * scale },
                                Vector2{ 0, 0 }, 0.0f, color);
                            x = x + 8 * scale;

                            break;
                        }
                        case '3':
                        {
                            DrawTexturePro(*Textures::Utils::GrabTexture(Textureid::FONT_LETTER_3),
                                           Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_3),
                                Rectangle{ (float)x, (float)newline, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_3).width * scale, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_3).height * scale },
                                           { 0, 0 }, 0.0f, color);
                            x = x + 8 * scale;
                            break;
                        }
                        case '4':
                        {
                            DrawTexturePro(*Textures::Utils::GrabTexture(Textureid::FONT_LETTER_4),
                                           Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_4),
                                Rectangle{ (float)x, (float)newline, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_4).width * scale, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_4).height * scale },
                                           { 0, 0 }, 0.0f, color);
                            x = x + 8 * scale;
                            break;
                        }
                        case '5':
                        {
                            DrawTexturePro(*Textures::Utils::GrabTexture(Textureid::FONT_LETTER_5),
                                           Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_5),
                                Rectangle{ (float)x, (float)newline, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_5).width * scale, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_5).height * scale },
                                           { 0, 0 }, 0.0f, color);
                            x = x + 8 * scale;
                            break;
                        }
                        case '6':
                        {
                            DrawTexturePro(*Textures::Utils::GrabTexture(Textureid::FONT_LETTER_6),
                                Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_6),
                                Rectangle{ (float)x, (float)newline, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_6).width * scale, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_6).height * scale },
                                Vector2{ 0, 0 }, 0.0f, color);
                            x = x + 8 * scale;

                            break;
                        }
                        case '7':
                        {
                            DrawTexturePro(*Textures::Utils::GrabTexture(Textureid::FONT_LETTER_7),
                                           Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_7),
                                           Rectangle{ (float)x, (float)newline, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_7).width * scale, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_7).height * scale },
                                           { 0, 0 }, 0.0f, color);
                            x = x + 8 * scale;
                            break;
                        }
                        case '8':
                        {
                            DrawTexturePro(*Textures::Utils::GrabTexture(Textureid::FONT_LETTER_8),
                                           Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_8),
                                Rectangle{ (float)x, (float)newline, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_8).width * scale, Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_8).height * scale },
                                           { 0, 0 }, 0.0f, color);
                            x = x + 8 * scale;
                            break;
                        }
                        case '9':
                        {
                            DrawTexturePro(*Textures::Utils::GrabTexture(Textureid::FONT_LETTER_9),
                                           Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_9),
                                Rectangle{ (float)x, (float)newline,
Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_9).width * scale,
Textures::Utils::GrabRectangle(Textureid::FONT_LETTER_9).height * scale },
                                           { 0, 0 }, 0.0f, color);
                            x = x + 8 * scale;
                            break;
                        }
                        case ' ':
                        {
                            x = x + 8 * scale;
                            break;
                        }
                        case '\n':
                        {
                            newline = newline + 8 * scale;
                            x = textloc.x;
                            break;
                        }
                        default:
                        {
                            x = x + 8 * scale;
                            break;
                        }
                    }
                }

                return;
            }


            bool DrawButton(std::string content,Rectangle textloc,float scale = 1,Color color = {255,255,255,255})
            {
                Vector2 init_mouse_pos = GetMousePosition();
                return false;
            }
        }
        Vector2 GetCenterOfTiles(int tileSize, int tilesPerRow, int totalTiles)
        {
            float minX = 1e9f;
            float minY = 1e9f;
            float maxX = -1e9f;
            float maxY = -1e9f;
        
            for (int i = 0; i < totalTiles; ++i) {
                int tx = i % tilesPerRow;
                int ty = i / tilesPerRow;
            
                float x = (float)(tx * tileSize);
                float y = (float)(ty * tileSize);
            
                if (x < minX) minX = x;
                if (y < minY) minY = y;
                if (x > maxX) maxX = x;
                if (y > maxY) maxY = y;
            }
        
            return {
                (minX + maxX) / 2.0f,
                (minY + maxY) / 2.0f
            };
        }
    }

    bool RenderMap(HeightMap hm)
    {
        if (Data::currentscene == mainmenu) { return true; }
        const int tileSize = 16;

        float carX = Data::Player.CarPosition.x;
        float carY = Data::Player.CarPosition.y;

        float halfMapOffsetX = -(255 * tileSize) / 2.0f;
        float halfMapOffsetY = -(255 * tileSize) / 2.0f;

        for (int y = 0; y < 255; y++)
            for (int x = 0; x < 255; x++)
            {
                unsigned char h = hm.HeightMapData[y][x];
                Color col = { h, h, h, 255 };

                Texture2D* a = Textures::Utils::GrabTexture(Textureid::PLAINS_Plain_empty);

                float worldX = x * tileSize + halfMapOffsetX;
                float worldY = y * tileSize + halfMapOffsetY;

                float screenX = worldX + carX;
                float screenY = worldY + carY;

                DrawTexturePro(*a, Textures::Utils::GrabRectangle(Textureid::PLAINS_Plain_empty), { screenX, screenY, tileSize, tileSize }, { 0,0 }, 0, col);
            }

        return true;
    }

    bool rendering_levelselect = false;
    LevelPreviewShown LevelPreviewBeingRendered = LevelPreviewShown::PLAINS;

    bool RenderScene(Scenes scene)
    {
        Vector2 mouseLogical = {
            GetMouseX() * ((float)Data::windowsize.x / GetMonitorWidth(0)),
            GetMouseY() * ((float)Data::windowsize.y / GetMonitorHeight(0))
        };

        switch (scene)
        {
            case mainmenu: 
            {
                Texture2D* txt = Textures::Utils::GrabTexture(Textureid::PLAINS_Plain_empty);
                Rectangle rect = Textures::Utils::GrabRectangle(Textureid::PLAINS_Plain_empty);
                Vector2 tmpvec = {0,0};
                while (tmpvec.y < Data::windowsize.y + 16)
                {
                    while (tmpvec.x < Data::windowsize.x + 16)
                    {
                        DrawTexturePro(*txt,rect,{tmpvec.x,tmpvec.y,8,8},{0,0},0,{192,192,192,255});
                        tmpvec.x = tmpvec.x + 8;
                    }
                    tmpvec.x = 0;
                    tmpvec.y = tmpvec.y + 8;
                }

                txt = Textures::Utils::GrabTexture(Textureid::PLAINS_Plain_Grass);
                rect = Textures::Utils::GrabRectangle(Textureid::PLAINS_Plain_Grass);
                tmpvec = {0,0};
                int count = 0;
                while (tmpvec.y < Data::windowsize.y + 16)
                {
                    while (tmpvec.x < Data::windowsize.x + 16)
                    {
                        count = count + 1;
                        if (count % 6 == 0)
                        {
                            DrawTexturePro(*txt,rect,{tmpvec.x,tmpvec.y,8,8},{0,0},0,{192,192,192,255});
                        }
                        tmpvec.x = tmpvec.x + 8;
                    }
                    tmpvec.x = 0;
                    tmpvec.y = tmpvec.y + 8;
                }
                
                DrawRectangle(0,5,Data::windowsize.x,40,{0,0,0,128});

               Render::Utils::UI::DrawText("BIG RIGS",{40,20,0,0},2,ORANGE);
               Render::Utils::UI::DrawText("(top down)",{20,10,0,0},1,RED);

                if (CheckCollisionRecs({55,50,30,10},{Debug::mouseposconverted.x,Debug::mouseposconverted.y,4,4}) == true)
                {
                   Render::Utils::UI::DrawText("Play",{55,50,0,0},1,DARKGRAY);
                    if (IsMouseButtonPressed(0) == true)
                    {
                        //reset bot n player data
                        Data::bot3.truckrotation = 90.0f;
                        Data::bot3.acceleration = 0;
                        Data::bot3.CarPosition = {};
                        Data::bot3.health = 100;

                        Data::Bot1.health = 100;
                        Data::Bot1.truckrotation = 90.0f;
                        Data::Bot1.CarPosition = {};
                        Data::Bot1.acceleration = 0;

                        Data::Bot2.truckrotation = 90.0f;
                        Data::Bot2.CarPosition = {};
                        Data::Bot2.acceleration = 0;
                        Data::Bot2.health = 100;
                        //sadly bots dont work atleast not yet...

                        Data::Player.truckrotation = 180.0f;
                        Data::Player.CarPosition = {114.6,198.4};
                        Data::Player.acceleration = 0;
                        Data::Player.health = 100;

                        Data::stop_thestopwatch = false;
                        Timer::stopwatch_timer = 0;
                        Timer::tmp = 0;

                        Collisions::reset();

                        SceneTransition::changescene(Scenes::Racemap_plains,0.5f,true);
                    }
                }else {
                   Render::Utils::UI::DrawText("Play",{55,50,0,0},1,WHITE);
                }

                if (CheckCollisionRecs({55,75,30,10},{mouseLogical.x,mouseLogical.y,4,4}) == true)
                {
                    Render::Utils::UI::DrawText("Quit",{55,75,0,0},1,DARKGRAY);
                    if (IsMouseButtonPressed(0) == true)
                    {
                        Data::running = false;
                    }
                }else {
                    Render::Utils::UI::DrawText("Quit",{55,75,0,0},1,WHITE);
                }

                auto map = Data::scoreleaderboard;
                map.insert({"USER", Data::pbscore});

                std::vector<std::pair<std::string, int>> sorted(map.begin(), map.end());

                std::sort(sorted.begin(), sorted.end(), [](const auto &a, const auto &b) {
                    return a.second > b.second;
                });

                for (size_t i = 0; i < 10 && i < sorted.size(); i++) {
                    const auto &entry = sorted[i];
                    float y = 80 + 10 * i;

                    Render::Utils::UI::DrawText(
                        std::to_string(i + 1),
                        Rectangle{95, y, 50, 20},
                        1.0f,
                        { 255, 255, 255, 255 }
                    );

                    Render::Utils::UI::DrawText(
                        entry.first,
                        Rectangle{110, y, 100, 20},
                        1.0f,
                        {255, 255, 255, 255}
                    );

                    Render::Utils::UI::DrawText(
                        std::to_string(entry.second),
                        Rectangle{150, y, 100, 20},
                        1.0f,
                        { 255, 255, 255, 255 }
                    );
                }

                break;
            }
            case Racemap_plains:
            {
                RenderMap(Data::maps::plains);
                break;
            }
            case Racemap_forest:
            {
                RenderMap(Data::maps::forest);
                break;
            }
            case Racemap_village:
            {
                RenderMap(Data::maps::village);
                break;
            }
            case Racemap_city:
            {
                RenderMap(Data::maps::city);
                break;
            }
            case Racemap_desert:
            {
                RenderMap(Data::maps::desert);
                break;
            }
            default:
                break;
        }
        return true;
    }

    bool RenderPlayer()
    {
        if (Data::currentscene == mainmenu) {return true;} 
        const int tileSize = 8;
        const int tilesPerRow = 6;
        const int totalTiles = 36;
        const int fullSize = tileSize * tilesPerRow; // 48

        Vector2 center = {Data::windowsize.x / 2,Data::windowsize.y / 2};

        float rotation = Data::Player.truckrotation * (PI / 180.0f);

        Texture* bigTruckTex = Textures::Utils::GrabTexture(Truck);
        if (!bigTruckTex) return false;

        Rectangle src = { 0, 0, (float)fullSize, (float)fullSize };
        Rectangle dst = { center.x, center.y, (float)fullSize /3, (float)fullSize /3 };

        Vector2 origin = { 0,0 };

        DrawTexturePro(*bigTruckTex, src, dst, origin, rotation * (180.0f / PI), WHITE);

        return true;
    }
}


