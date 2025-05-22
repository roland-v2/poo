#pragma once

#include "libs/SDL2/include/SDL.h"
#include "libs/SDL2/include/SDL_image.h"
#include <iostream>
using namespace std;

namespace OOP_Game {
    class Object {
    public:
        // Constructor
        Object() {m_solid = true;};

        // Destination methods
        SDL_Rect GetDest() const {return m_dest;}
        void SetDest(int x, int y, int w, int h);
        void SetDest(int x, int y);
        int GetDX() const {return m_dest.x;}
        int GetDY() const {return m_dest.y;}
        int GetDW() const {return m_dest.w;}
        int GetDH() const {return m_dest.h;}

        // Source methods
        void SetSrc(int x, int y, int w, int h);
        SDL_Rect GetSrc() const {return m_src;}

        // Texture/image methods
        void SetImage(string filename, SDL_Renderer *renderer);
        SDL_Texture *GetTex() const {return m_tex;}

        // Solid methods
        void SetSolid(bool s) {m_solid = s;}
        bool GetSolid()const {return m_solid;}

        // ID methods for map tiles
        void SetID(int i) {m_id = i;}
        int GetID() const {return m_id;}
    private:
        // Destination rectangle
        SDL_Rect m_dest;
        // Source rectangle
        SDL_Rect m_src;
        // Texture
        SDL_Texture *m_tex;
        // Solid flag
        bool m_solid;
        // ID for map tiles
        int m_id;
    };
}