#include "include/object.h"

namespace OOP_Game {
    // Destination methods
    void Object::SetDest(int x, int y, int w, int h) {
        m_dest.x = x;
        m_dest.y = y;
        m_dest.w = w;
        m_dest.h = h;
    }

    void Object::SetDest(int x, int y) {
        m_dest.x = x;
        m_dest.y = y;
    }

    // Source method
    void Object::SetSrc(int x, int y, int w, int h) {
        m_src.x = x;
        m_src.y = y;
        m_src.w = w;
        m_src.h = h;
    }

    // Image method
    void Object::SetImage(string filename, SDL_Renderer *renderer) {
        m_tex = IMG_LoadTexture(renderer, filename.c_str());
    }
}