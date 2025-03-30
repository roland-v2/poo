#pragma once

#include "object.h"
#include </opt/homebrew/include/SDL2/SDL.h>
#include </opt/homebrew/include/SDL2/SDL_image.h>
#include </opt/homebrew/include/SDL2/SDL_ttf.h>
#include </opt/homebrew/include/SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>

class Entity : public Object {
public:
    void setHealth(int h) {health = h;}
    void setMaxHealth(int h) {maxHealth = h;}
    int getHealth() const {return health;}
    int getMaxHealth() const {return maxHealth;}
    int createCycle(int r, int w, int h, int amount, int speed);
    void setCurrAnim(int c) {begin = 0; currAnim = c;}
    void updateAnimation();
private:
    int health, maxHealth;
    struct cycle {
        int row;
        int w;
        int h;
        int amount;
        int speed;
        int tick;
    };
    vector <cycle> animations;
    int currAnim;
    int begin;
};