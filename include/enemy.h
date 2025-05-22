#pragma once

#include "entity.h"

namespace OOP_Game {
    // Forward declaration
    class Player;

    // Enemy class inherits from Entity
    class Enemy : public Entity {
    public:
        // Constructor
        Enemy();
        
        // Copy constructor and assignment operator
        Enemy(const Enemy& other);
        Enemy& operator=(const Enemy& other);
        
        // Range and attack methods
        bool IsInRange(int x, int y);
        void SetRange(int r) { m_range = r; }
        int GetRange() const { return m_range; }
        void Attack(Player &target, int amount);
        bool CanAttack() const { return m_attack_ready; }

        // Cooldown method
        void UpdateCooldown();
        void ResetAttackCooldown();

        // Movement method
        void MoveTowards(int x, int y, float speed);

        // Damage method
        void TakeDamage(int amount) override;

        // Overloading + operator
        friend int operator+(const Enemy& enemy1_health, const Enemy& enemy2_health);
    private:
        // Enemy attributes
        int m_range;    
        int m_amount;
        bool m_attack_ready;
        int m_life;
        // Last attack time
        Uint32 m_last_attack_time;
        // Attack cooldown in milliseconds
        static const Uint32 m_attack_cooldown = 2000;    
    };
}