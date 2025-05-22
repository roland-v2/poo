#include "include/object.h"

namespace OOPGame {
    // Destination methods
    void Object::SetDest(int x, int y, int w, int h) {
        dest.x = x;
        dest.y = y;
        dest.w = w;
        dest.h = h;
    }

    void Object::SetDest(int x, int y) {
        dest.x = x;
        dest.y = y;
    }

    // Source method
    void Object::SetSrc(int x, int y, int w, int h) {
        src.x = x;
        src.y = y;
        src.w = w;
        src.h = h;
    }

    // Image method
    void Object::SetImage(string filename, SDL_Renderer *renderer) {
        tex = IMG_LoadTexture(renderer, filename.c_str());
    }
}