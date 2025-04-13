#include "object.h"

void Object::setDest(int x, int y, int w, int h) {
    dest.x = x;
    dest.y = y;
    dest.w = w;
    dest.h = h;
}

void Object::setDest(int x, int y) {
    dest.x = x;
    dest.y = y;
}

void Object::setSrc(int x, int y, int w, int h) {
    src.x = x;
    src.y = y;
    src.w = w;
    src.h = h;
}

void Object::setImage(string filename, SDL_Renderer *renderer) {
    SDL_Surface *surf = IMG_Load(filename.c_str());
    //tex = SDL_CreateTextureFromSurface(renderer, surf);
    tex = IMG_LoadTexture(renderer, filename.c_str());
}