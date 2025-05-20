#pragma once

#include "entity.h"
#include </opt/homebrew/include/SDL2/SDL.h>
#include </opt/homebrew/include/SDL2/SDL_image.h>
#include </opt/homebrew/include/SDL2/SDL_ttf.h>
#include </opt/homebrew/include/SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>
#include <string>

class Player : public Entity {
public:
    Player();
    ~Player() = default;
    
    // Score methods
    void AddScore(int points);
    void ResetScore();
    int GetScore() const;
    
    // Lives methods
    void SetLives(int lives);
    int GetLives() const;
    void LoseLife();
    bool IsAlive() const;
    
    // Health methods
    void TakeDamage(int amount);
    
private:
    // Score
    int score;
    
    // Lives
    int lives;
};