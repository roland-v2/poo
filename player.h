#pragma once

#include "entity.h"
#include "enemy.h"

// Forward declaration
class Enemy;

// Player class inherits from Entity
class Player : public Entity {
public:
    // Constructor
    Player();
    
    // Score methods
    int GetScore() const { return score; };
    void AddScore(int points) { score += points; };

    // Lives methods
    void SetLives(int lives) { this->lives = lives; };
    int GetLives() const { return lives; };
    void LoseLife();

    // Health/damage methods
    void TakeDamage(int amount);
    void AttackEnemy(Enemy &target, int amount);
    bool IsAlive() const { return lives > 0; };

    // Range methods
    bool EnemyIsInRange(int x, int y);
    void SetRange(int r) { rangePlayer = r; }
    int GetRange() const { return rangePlayer; }
    
private:
    // Player attributes
    int score;
    int lives;
    int rangePlayer;
};