#pragma once

#include "entity.h"
#include "player.h"
#include </opt/homebrew/include/SDL2/SDL.h>
#include </opt/homebrew/include/SDL2/SDL_image.h>
#include </opt/homebrew/include/SDL2/SDL_ttf.h>
#include </opt/homebrew/include/SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>
#include <string>

class Enemy : public Entity {
public:
    Enemy();
    ~Enemy();
    
    bool IsInRange(int x, int y);
    void SetRange(int r) { range = r; }
    int GetRange() const { return range; }
    void Attack(Player &target, int amount);
    void MoveTowards(int x, int y);
    
    // Cooldown methods
    bool CanAttack() const;
    void ResetAttackCooldown();
    void UpdateCooldown();

private:
    int range; // Attack range
    int amount;
    
    // Cooldown variables
    Uint32 lastAttackTime;
    const Uint32 attackCooldown = 2000; // 2 seconds in milliseconds
    bool attackReady;
};