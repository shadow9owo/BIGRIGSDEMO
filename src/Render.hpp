#include "Types.h"
#include <string>

namespace Render
{
    namespace Utils {
        namespace UI
        {
            extern void DrawWindow();
            extern Rectangle GetTextLenght(std::string content,float scale);
            extern void DrawText(std::string content,Rectangle textloc,float scale,Color color);
            extern bool DrawButton(std::string content,Rectangle textloc,float scale,Color color);
        }
        namespace Particles
        {
            extern bool RenderParticles();
            extern void ParticlePhysics();
        }
    }
    extern bool RenderScene(Scenes scene);
    extern bool rendering_levelselect;
    extern LevelPreviewShown LevelPreviewBeingRendered;
    extern bool RenderPlayer();
    extern bool RenderMap(HeightMap heightmap);
} 
