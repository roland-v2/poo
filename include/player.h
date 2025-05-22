#pragma once

#include "entity.h"
#include "enemy.h"
#include <iostream>

namespace OOP_Game {
    // Forward declaration
    class Enemy;

    // Player class inherits from Entity
    class Player : public Entity {
    public:
        // Constructor
        Player();
        
        // Score methods
        int GetScore() const { return m_score; };
        void AddScore(int points) { m_score += points; };

        // Lives methods
        void SetLives(int lives) { this->m_lives = lives; };
        int GetLives() const { return m_lives; };
        void LoseLife();

        // Health/damage methods
        void TakeDamage(int amount) override;
        void AttackEnemy(Enemy &target, int amount);
        void AttackBossEnemy(Enemy &target, int amount);
        void AttackBossEnemy(Enemy &target);
        bool IsAlive() const { return m_lives > 0; };
        void SetDamage(int d) { m_damage = d; };
        int GetDamage() const { return m_damage; };

        // Range methods
        bool EnemyIsInRange(int x, int y);
        void SetRange(int r) { m_range_player = r; }
        int GetRange() const { return m_range_player; }

        // Overloading << operator
        friend std::ostream& operator<<(std::ostream& os, const Player& player);
    private:
        // Player attributes
        int m_score;
        int m_lives;
        int m_range_player;
        int m_damage;
    };
}