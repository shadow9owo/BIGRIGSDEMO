#include <raylib.h>
#include "Types.h"

namespace SceneTransition
{   
    extern bool transitioning;
    extern float timeleft;
    extern Scenes _scene;
    extern void transitioncallbacks();
    extern void changescene(Scenes scene,float time,bool showoverlay);
}