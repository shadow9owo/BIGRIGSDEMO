#include <raylib.h>
#include "Data.hpp"
#include "Render.hpp"
#include "texturemanager.hpp"
#include "Input.hpp"
#include "Sounds.hpp"
#include "Debug.hpp"
#include "Save.hpp"
#include "maps.hpp"
#include "Collision.hpp"
#include "Audio.hpp"
#include "Logger.hpp"
#include "Timer.hpp"
#include "SceneTransitions.hpp"

int main(void)
{

    InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "TOP DOWN Big Rigs");
    InitAudioDevice(); 
    SetAudioStreamBufferSizeDefault(4096);

    RenderTexture2D target = LoadRenderTexture(Data::windowsize.x, Data::windowsize.y);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);

    if (!IsWindowFullscreen())
    {
        ToggleFullscreen();
    }

    SetTargetFPS(24);
    SetExitKey(0);

    Save::init();

    try
    {
        if (!Textures::_LoadTextures())
        {
            return -1;
        }
        Save::Load();
        Data::maps::generateheightmaps();
        sounds::LoadSounds();
        Maps::LoadMap("./assets/map1.tmx",Data::camera);
    }
    catch (const std::exception& e)
    {
        Logger::AddToLoggerBuffer(e.what());
    }

    Data::camera.target = { 0, 0 };
    Data::camera.offset = { 0,0 };
    Data::camera.rotation = 0.0f;
    Data::camera.zoom = 1.0f;

    while (!WindowShouldClose() && Data::running)
    {
        BeginTextureMode(target);
            if (!Data::paused && !SceneTransition::transitioning)
            {
                if (!Data::stop_thestopwatch)
                {
                    Timer::count();
                }
            }
            Data::tick = (Data::tick + 1) % 25;
            if (Data::currentscene != mainmenu)
            {
                ClearBackground(DARKGREEN);
            }else {
                ClearBackground(BLACK);
            }

            BeginMode2D(Data::camera);

            if (IsWindowFocused())
            {
                if (!Data::paused)
                {
                    if (Collisions::collides(Maps::Map))
                    {
                        Data::Player.acceleration = Data::Player.acceleration * 0.2f;
                    }
                }
                Input::ListenForInput();
            }
            
            bool res = (Render::RenderScene(Data::currentscene) && Maps::DrawMap() && Render::Utils::Particles::RenderParticles() && Render::RenderPlayer() && Audio::Stream());

            Collisions::check();
            Timer::Render();

            if (Data::debug)
            {
                DrawCircle(Debug::mouseposconverted.x,Debug::mouseposconverted.y,4,RED);
            }
            if (!res)
            {
                Logger::AddToLoggerBuffer("Rendering error");
            }

            EndMode2D();

            SceneTransition::transitioncallbacks();

        EndTextureMode();

        BeginDrawing();
            ClearBackground(BLACK);

            DrawTexturePro(target.texture,
                Rectangle{ 0, 0, (float)Data::windowsize.x, -(float)Data::windowsize.y },
                Rectangle{ 0, 0, (float)GetMonitorWidth(0), (float)GetMonitorHeight(0) },
                Vector2{ 0, 0 }, 0.0f, WHITE);
            
                Debug::render_debug_text();
                Logger::RenderLogger();
                if (Data::paused && Data::currentscene != mainmenu)
                {
                    DrawText("PAUSED",0,0,32,WHITE);
                }
        EndDrawing();
    }
    Save::Save();

    Maps::UnloadMap();
    UnloadRenderTexture(target);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}