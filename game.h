#pragma once

#include "object.h"
#include "audio.h"
#include "entity.h"
#include "player.h"
#include "menu.h"
#include </opt/homebrew/include/SDL2/SDL.h>
#include </opt/homebrew/include/SDL2/SDL_image.h>
#include </opt/homebrew/include/SDL2/SDL_ttf.h>
#include </opt/homebrew/include/SDL2/SDL_mixer.h>
#include <iostream>
#include <fstream>
#include <vector>

#define Width 1280
#define Height 720
#define Tile_size 25
#define Gravity 10

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
    void LoadMap(const char *filename);
    void DrawMap();
    void Scroll(int x, int y);
    bool Collision(Object a, Object b);
private:
    SDL_Renderer *renderer;
    SDL_Window *window;
    TTF_Font *font;
    bool running;
    int count;
    int frameCount, timerFPS, lastFrame;
    int mouse_x, mouse_y;
    Player player;
    vector<Object> map;
    int mapX, mapY;
    int playerSpeed;
    bool l=0, r=0, u=0, d=0;
    int idol, run;
    bool canMove;
    Menu menu;
};