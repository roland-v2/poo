#pragma once

#include </opt/homebrew/include/SDL2/SDL.h>
#include </opt/homebrew/include/SDL2/SDL_image.h>
#include </opt/homebrew/include/SDL2/SDL_ttf.h>
#include </opt/homebrew/include/SDL2/SDL_mixer.h>
#include <iostream>
using namespace std;

class Object {
private:
    SDL_Rect dest;
    SDL_Rect src;
    SDL_Texture *tex;
public:
    Object() {};
    SDL_Rect getDest() const {return dest;}
    SDL_Rect getSrc() const {return src;}
    void setDest(int x, int y, int w, int h);
    void setSrc(int x, int y, int w, int h);
    void setImage(string filename, SDL_Renderer *renderer);
    SDL_Texture *getTex() const {return tex;}
};