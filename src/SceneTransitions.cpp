#include "SceneTransitions.hpp"
#include <raylib.h>
#include "Data.hpp"

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
            if (timeleft < 0)
            {
                transitioning = false;
                timeleft = 0;
                Data::currentscene = _scene;
                overlay = true;
                return;
            }else {
                timeleft = timeleft - GetFrameTime();
            }
            if (overlay)
            {
                DrawRectangle(0,0,Data::windowsize.x,Data::windowsize.y,{0,0,0,128});
            }
        }
        return;
    }

    void changescene(Scenes scene,float time,bool showoverlay)
    {
        Data::currentscene = scene;
        return;
    }
}