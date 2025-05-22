#pragma once

#include "entity.h"

namespace OOPGame {
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
        void SetRange(int r) { range = r; }
        int GetRange() const { return range; }
        void Attack(Player &target, int amount);
        bool CanAttack() const { return attackReady; }

        // Cooldown method
        void UpdateCooldown();
        void ResetAttackCooldown();

        // Movement method
        void MoveTowards(int x, int y, float speed);

        // Damage method
        void TakeDamage(int amount) override;

        // Overloading + operator
        friend int operator+(const Enemy& lhs, const Enemy& rhs);
    private:
        // Enemy attributes
        int range;    
        int amount;
        bool attackReady;
        int life;
        // Last attack time
        Uint32 lastAttackTime;
        // Attack cooldown in milliseconds
        static const Uint32 ATTACK_COOLDOWN = 2000;    
    };
}