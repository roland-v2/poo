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
    SDL_Rect GetDest() const {return dest;}
    SDL_Rect GetSrc() const {return src;}
    void SetDest(int x, int y, int w, int h);
    void SetDest(int x, int y);
    void SetSrc(int x, int y, int w, int h);
    void SetImage(string filename, SDL_Renderer *renderer);
    SDL_Texture *GetTex() const {return tex;}
    void SetSolid(bool s) {solid = s;}
    bool GetSolid()const {return solid;}
    int GetDX() const {return dest.x;}
    int GetDY() const {return dest.y;}
    int GetDW() const {return dest.w;}
    int GetDH() const {return dest.h;}
    void SetID(int i) {id = i;}
    int GetID() const {return id;};
};