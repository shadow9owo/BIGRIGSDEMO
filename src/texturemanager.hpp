#pragma once

#include <string.h>
#include "Types.h"
#include <raylib.h>

namespace Textures
{
    namespace Utils
    {
        extern bool UnloadAll();
        extern bool LoadAllInScene(Scenes scene);
        extern bool IsIdLoaded(Textureid id);
        extern bool LoadAll();

        extern Texture* GrabTexture(Textureid id);
        extern Texture* GrabTileTexture(Textureid id, int index);

        extern void LoadTextureById(Textureid id);

        extern Texture BuildBigTextureFromTiles(Textureid id);

        extern Rectangle GrabRectangle(Textureid id);
    }

    extern int availiblevramMBs();
    extern bool _LoadTextures();
}
