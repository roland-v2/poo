#pragma once

#include "entity.h"
#include </opt/homebrew/include/SDL2/SDL.h>
#include </opt/homebrew/include/SDL2/SDL_image.h>
#include </opt/homebrew/include/SDL2/SDL_ttf.h>
#include </opt/homebrew/include/SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

// Forward declaration
class Enemy;

class Player : public Entity {
public:
    Player();
    
    // Score methods
    void AddScore(int points);
    void ResetScore();
    int GetScore() const;
    
    // Lives methods
    void SetLives(int lives);
    int GetLives() const;
    void LoseLife();
    bool IsAlive() const;
    
    // Health/damage methods
    void TakeDamage(int amount);
    
    void AttackEnemy(Enemy &target, int amount);
    bool EnemyIsInRange(int x, int y);
    void SetRange(int r) { rangePlayer = r; }
    int GetRange() const { return rangePlayer; }
    
private:
    int score;
    int lives;
    int rangePlayer;
};