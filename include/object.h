#pragma once

#include "libs/SDL2/include/SDL.h"
#include "libs/SDL2/include/SDL_image.h"
#include <iostream>
using namespace std;

namespace OOPGame {
    class Object {
    public:
        // Constructor
        Object() {solid = true;};

        // Destination methods
        SDL_Rect GetDest() const {return dest;}
        void SetDest(int x, int y, int w, int h);
        void SetDest(int x, int y);
        int GetDX() const {return dest.x;}
        int GetDY() const {return dest.y;}
        int GetDW() const {return dest.w;}
        int GetDH() const {return dest.h;}

        // Source methods
        void SetSrc(int x, int y, int w, int h);
        SDL_Rect GetSrc() const {return src;}

        // Texture/image methods
        void SetImage(string filename, SDL_Renderer *renderer);
        SDL_Texture *GetTex() const {return tex;}

        // Solid methods
        void SetSolid(bool s) {solid = s;}
        bool GetSolid()const {return solid;}

        // ID methods for map tiles
        void SetID(int i) {id = i;}
        int GetID() const {return id;}
    private:
        // Destination rectangle
        SDL_Rect dest;
        // Source rectangle
        SDL_Rect src;
        // Texture
        SDL_Texture *tex;
        // Solid flag
        bool solid;
        // ID for map tiles
        int id;
    };
}