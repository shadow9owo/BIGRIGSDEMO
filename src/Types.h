#pragma once

typedef struct Vector2I
{
    int x;
    int y;
}Vector2I;

typedef struct HeightMap
{
    unsigned char HeightMapData[255][255];
    int seed;
}HeightMap;

enum Scenes
{
    mainmenu = 0,
    Racemap_village,
    Racemap_city,
    Racemap_plains,
    Racemap_desert,
    Racemap_forest
};

enum Textureid
{
    None = -1,
    Truck = 0,
    PLAINS_Plain_empty = 1,
    PLAINS_Road_0deg = 2,
    PLAINS_Road_Turn = 3,
    PLAINS_Road_90deg = 4,
    PLAINS_Plain_Grass = 5,
    PLAINS_Treetop = 6,
    PLAINS_Treebot = 7,
    PLAINS_Tree2top = 8,
    PLAINS_Tree2bot = 9,
    UI_CORNER_FILLED = 10,
    UI_FILLED_LINE = 11,
    UI_BG_FILLED = 12,
    UI_CORNER_EMPTY_BR = 13,
    UI_CORNER_ROUND_EMPTY_1 = 14,
    UI_CORNER_ROUND_EMPTY_2 = 15,
    UI_VERT_EMPTY = 16,
    UI_VERT_END = 17,
    UI_SLAB = 18,
    UI_HORIZONTAL = 19,
    UI_SHARP_EDGE = 20,
    UI_SHORT_BLOCKY_TURN = 21,
    UI_CORNER_BLOCKY2 = 22,
    FONT_LETTER_R = 23,
    FONT_LETTER_S = 24,
    FONT_LETTER_1 = 25,
    FONT_LETTER_Q = 26,
    FONT_LETTER_T = 27,
    FONT_LETTER_2 = 28,
    FONT_LETTER_P = 29,
    FONT_LETTER_U = 30,
    FONT_LETTER_3 = 31,
    FONT_LETTER_N = 32,
    FONT_LETTER_O = 33,
    FONT_LETTER_V = 34,
    FONT_LETTER_4 = 35,
    FONT_LETTER_F = 36,
    FONT_LETTER_M = 37,
    FONT_LETTER_W = 38,
    FONT_LETTER_5 = 39,
    FONT_LETTER_C = 40,
    FONT_LETTER_E = 41,
    FONT_LETTER_G = 42,
    FONT_LETTER_L = 43,
    FONT_LETTER_X = 44,
    FONT_LETTER_6 = 45,
    FONT_LETTER_A = 46,
    FONT_LETTER_H = 47,
    FONT_LETTER_K = 48,
    FONT_LETTER_Y = 49,
    FONT_LETTER_7 = 50,
    FONT_LETTER_B = 51,
    FONT_LETTER_D = 52,
    FONT_LETTER_I = 53,
    FONT_LETTER_J = 54,
    FONT_LETTER_Z = 55,
    FONT_LETTER_8 = 56,
    FONT_LETTER_9 = 57,
    FONT_LETTER_0 = 58,
    PLAINS_PLAIN_GRASS_2 = 59,
    PLAINS_ROAD_WHOLE = 60,
    Collision = 61,
    Winner = 62
};

enum Bot
{
    Player = 0,
    Bot1 = 1,
    Bot2 = 3,
    Bot3 = 4
};

typedef struct _Truck
{
    float acceleration;
    Bot botidentifier;
    Vector2 CarPosition;
    float truckrotation;
    int health;
}_Truck;

typedef struct Particle
{
    float rotation;
    Color color;
    int texture;
    Rectangle sizepos;
}Particle;

enum LevelPreviewShown //other is not implemented
{
    PLAINS
};