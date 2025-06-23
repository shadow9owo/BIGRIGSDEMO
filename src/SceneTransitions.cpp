#include "SceneTransitions.hpp"
#include <raylib.h>
#include "Data.hpp"
#include "texturemanager.hpp"
#include "Logger.hpp"

namespace SceneTransition
{
    bool transitioning = false;
    float timeleft = 0;
    bool overlay = true;
    Scenes _scene;

    void transitioncallbacks()
    {
        if (transitioning)
        {
            timeleft = timeleft - GetFrameTime();

            if (timeleft <= 0)
            {
                transitioning = false;
                timeleft = 0;
                Data::currentscene = _scene;
                overlay = true;
                return;
            }
            if (_scene == mainmenu)
            {
                Texture2D* tex = Textures::Utils::GrabTexture(Winner);
                if (tex && tex->id != 0)
                {
                    Rectangle src = { 0, 0, (float)tex->width, (float)tex->height };
                    Rectangle dst = { 20, 20, (float)tex->width, (float)tex->height };
                    DrawTexturePro(*tex, src, dst, { 0, 0 }, 0, WHITE);
                }
            }
        }
    }

    void changescene(Scenes scene, float time, bool showoverlay)
    {
        if (!transitioning) 
        {
            _scene = scene;
            timeleft = time;
            overlay = showoverlay;
            transitioning = true;
        }
    }
}
