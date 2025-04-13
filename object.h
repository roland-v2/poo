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
    bool solid;
    int id;
public:
    Object() {solid = 1;};
    SDL_Rect getDest() const {return dest;}
    SDL_Rect getSrc() const {return src;}
    void setDest(int x, int y, int w, int h);
    void setDest(int x, int y);
    void setSrc(int x, int y, int w, int h);
    void setImage(string filename, SDL_Renderer *renderer);
    SDL_Texture *getTex() const {return tex;}
    void setSolid(bool s) {solid = s;}
    bool getSolid()const {return solid;}
    int getDX() const {return dest.x;}
    int getDY() const {return dest.y;}
    int getDW() const {return dest.w;}
    int getDH() const {return dest.h;}
    void setID(int i) {id = i;}
    int getID() const {return id;};
};