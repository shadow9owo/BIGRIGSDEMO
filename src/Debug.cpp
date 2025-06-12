#include "Debug.hpp"
#include <raylib.h>
#include "Data.hpp"
#include <iostream>

namespace Debug
{
    Vector2 mouseposconverted = {};
    void render_debug_text()
    {
        mouseposconverted.x = GetMousePosition().x * ((float)Data::windowsize.x / GetMonitorWidth(0));
        mouseposconverted.y = GetMousePosition().y * ((float)Data::windowsize.y / GetMonitorHeight(0));
        if (!Data::debug) return;

        DrawText(std::to_string(GetFPS()).c_str(), 0, 0, 16, GREEN);
        DrawText(std::to_string(GetMousePosition().x).c_str(), 0, 16, 16, GREEN);
        DrawText(std::to_string(GetMousePosition().y).c_str(), 0, 32, 16, GREEN);
        DrawText(std::to_string(GetMousePosition().x * ((float)Data::windowsize.x / GetMonitorWidth(0))).c_str(), 0, 48, 16, GREEN);
        DrawText(std::to_string(GetMousePosition().y * ((float)Data::windowsize.y / GetMonitorHeight(0))).c_str(), 0, 64, 16, GREEN);
        DrawText(std::to_string(Data::Player.CarPosition.x).c_str(), 0, 80, 16, GREEN);
        DrawText(std::to_string(Data::Player.CarPosition.y).c_str(), 0, 96, 16, GREEN);
    }
}
