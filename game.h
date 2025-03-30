#pragma once

#include "object.h"
#include </opt/homebrew/include/SDL2/SDL.h>
#include </opt/homebrew/include/SDL2/SDL_image.h>
#include </opt/homebrew/include/SDL2/SDL_ttf.h>
#include </opt/homebrew/include/SDL2/SDL_mixer.h>
#include <iostream>

class Game {
public:
    Game();
    ~Game();
    void Loop();
    void Update() {};
    void Input() {};
    void Render();
    void Draw(Object o);
    void Draw(const char *msg, int x, int y, int r, int g, int b, int size);
private:
    SDL_Renderer *renderer;
    SDL_Window *window;
    bool running;
    int count;
    int frameCount, timerFPS, lastFrame;
    Object star;
};