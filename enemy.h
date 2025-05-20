#pragma once

#include "entity.h"
#include </opt/homebrew/include/SDL2/SDL.h>
#include </opt/homebrew/include/SDL2/SDL_image.h>
#include </opt/homebrew/include/SDL2/SDL_ttf.h>
#include </opt/homebrew/include/SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>
#include <string>

// Forward declaration
class Player;

class Enemy : public Entity {
public:
    Enemy();
    ~Enemy();
    
    // Copy constructor and assignment operator
    Enemy(const Enemy& other);
    Enemy& operator=(const Enemy& other);
    
    bool IsInRange(int x, int y);
    void SetRange(int r) { range = r; }
    int GetRange() const { return range; }
    void Attack(Player &target, int amount);
    void MoveTowards(int x, int y);
    
    // Cooldown methods
    bool CanAttack() const;
    void ResetAttackCooldown();
    void UpdateCooldown();

    void TakeDamageE(int amount);

private:
    int range;    
    int amount;
    Uint32 lastAttackTime;
    // Make this static const instead of instance const
    static const Uint32 ATTACK_COOLDOWN = 2000;    
    bool attackReady;
    int life;
};