#include "Sounds.hpp"
#include <raylib.h>
#include "Data.hpp"

namespace Audio
{
    bool Stream()
    {
        switch (Data::currentscene)
        {
            case mainmenu:
                if (IsMusicStreamPlaying(sounds::Music_Menu))
                {
                    UpdateMusicStream(sounds::Music_Menu);
                }else {
                    PlayMusicStream(sounds::Music_Menu);
                }
                break;
            case Racemap_plains:
                if (IsMusicStreamPlaying(sounds::Music_Race1))
                {
                    UpdateMusicStream(sounds::Music_Race1);
                }else {
                    PlayMusicStream(sounds::Music_Race1);
                }
                break;
            default:
                break;
        }
        return true;
    }
    void unload()
    {
        UnloadMusicStream(sounds::Music_Race1);
        UnloadMusicStream(sounds::Music_Menu);
    }
}