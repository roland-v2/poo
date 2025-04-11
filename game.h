#pragma once

#include "object.h"
#include "audio.h"
#include "entity.h"
#include </opt/homebrew/include/SDL2/SDL.h>
#include </opt/homebrew/include/SDL2/SDL_image.h>
#include </opt/homebrew/include/SDL2/SDL_ttf.h>
#include </opt/homebrew/include/SDL2/SDL_mixer.h>
#include <iostream>
#include <fstream>
#include <vector>

#define Width 1280
#define Height 720
#define Tile_size 5

class Game {
public:
    Game();
    ~Game();
    void Loop();
    void Update();
    void Input();
    void Render();
    void Draw(Object o);
    void Draw(const char *msg, int x, int y, int r, int g, int b);
    void loadMap(const char *filename);
    void drawMap();
    void scroll();
private:
    SDL_Renderer *renderer;
    SDL_Window *window;
    TTF_Font *font;
    bool running;
    int count;
    int frameCount, timerFPS, lastFrame;
    int mouse_x, mouse_y;
    Entity player;
    vector<Object> map;
    int mapX, mapY;
};