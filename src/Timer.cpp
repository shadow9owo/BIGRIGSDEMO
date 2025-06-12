#include <raylib.h>
#include "Data.hpp"
#include "Timer.hpp"

namespace Timer
{
    float tmp;
    int stopwatch_timer;
    void count()
    {
        if (Data::currentscene == mainmenu) {return;}
        if (Data::stop_thestopwatch) return;
        tmp = tmp + GetFrameTime();
        stopwatch_timer = (int)tmp;
        return;
    }

    void Render()
    {
        if (Data::currentscene == mainmenu) return; 

        DrawText((std::to_string(Data::lap) + "/3").c_str(),100,20,24,WHITE);
        
        float totalSecs = tmp;

        int minutes    = int(totalSecs) / 60;
        int seconds    = int(totalSecs) % 60;
        int hundredths = int((totalSecs - int(totalSecs)) * 100);

        char buffer[26];
        snprintf(buffer, sizeof(buffer), "%02d:%02d.%02d", minutes, seconds, hundredths);

        int fontSize = 8;
        int textWidth  = MeasureText(buffer, fontSize);
        int textHeight = fontSize;

        int x = Data::windowsize.x / 2 - textWidth  / 2;
        int y = Data::windowsize.y / 4; 

        DrawText(buffer, x, y, fontSize, WHITE);
        return;
    }
}