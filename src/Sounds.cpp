#include <raylib.h>

namespace sounds
{
    Sound Sound_Horn;
    Sound Sound_Crash;
    Sound Sound_Drift;
    Sound Sound_Gameover;
    Sound Sound_Boost;
    Music Music_Race1;
    Music Music_Credits;
    Music Music_Menu;

    void LoadSounds()
    {
        Sound_Horn = LoadSound("./assets/CarHorn.ogg");
        SetSoundVolume(Sound_Horn, 0.5f);
        Sound_Crash = LoadSound("./assets/Crash.ogg");
        Sound_Drift = LoadSound("./assets/Drift.ogg");
        Sound_Gameover = LoadSound("./assets/GameOver.ogg");
        Sound_Boost = LoadSound("./assets/Boost.ogg");
        SetSoundVolume(Sound_Boost,0.2f);
        Music_Credits = LoadMusicStream("./assets/credits.ogg");
        Music_Menu = LoadMusicStream("./assets/menu.ogg");
        Music_Race1 = LoadMusicStream("./assets/race1.ogg");
        return;
    }
}