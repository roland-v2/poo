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
    void SetHealth(int h) {health = h;}
    void SetMaxHealth(int h) {maxHealth = h;}
    int GetHealth() const {return health;}
    int GetMaxHealth() const {return maxHealth;}
    int CreateCycle(int r, int w, int h, int amount, int speed);
    void SetCurrAnim(int c) {begin = 0; currAnim = c;}
    int GetCurrAnim() const {return currAnim;}
    void UpdateAnimation();
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