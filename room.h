#pragma once

#include </opt/homebrew/include/SDL2/SDL.h>
#include </opt/homebrew/include/SDL2/SDL_image.h>
#include </opt/homebrew/include/SDL2/SDL_ttf.h>
#include </opt/homebrew/include/SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

class Room {
private:
    int GetRoomID() const {return id;}
    void SetRoomID(int id) {this->id = id;}
    bool IsCleared() const {return cleared;}
public:
    int id;
    bool cleared;
};