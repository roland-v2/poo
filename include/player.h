#pragma once

#include "entity.h"
#include "enemy.h"
#include <iostream>

namespace OOPGame {
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
        void TakeDamage(int amount) override;
        void AttackEnemy(Enemy &target, int amount);
        void AttackBossEnemy(Enemy &target, int amount);
        void AttackBossEnemy(Enemy &target);
        bool IsAlive() const { return lives > 0; };
        void SetDamage(int d) { damage = d; };
        int GetDamage() const { return damage; };

        // Range methods
        bool EnemyIsInRange(int x, int y);
        void SetRange(int r) { rangePlayer = r; }
        int GetRange() const { return rangePlayer; }  
        
        // Overloading << operator
        friend std::ostream& operator<<(std::ostream& os, const Player& player);
    private:
        // Player attributes
        int score;
        int lives;
        int rangePlayer;
        int damage;
    };
}