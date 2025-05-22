#include "enemy.h"
#include "player.h"
#include <cmath>
#include </opt/homebrew/include/SDL2/SDL.h>

namespace OOPGame {
    // Default initialization of enemy attributes
    Enemy::Enemy() :
        range(25),
        amount(10),
        lastAttackTime(0),
        attackReady(true),
        life(50)
    {
        SetHealth(50);
        SetMaxHealth(50);
    }

    // Implement copy constructor
    // This constructor initializes the enemy with the same attributes as another enemy at creation
    Enemy::Enemy(const Enemy& other) : Entity(other) {
        range = other.range;
        amount = other.amount;
        lastAttackTime = other.lastAttackTime;
        attackReady = other.attackReady;
        life = other.life;
    }

    // Implement copy assignment operator
    // This operator assigns the attributes of one enemy to another after creation
    Enemy& Enemy::operator=(const Enemy& other) {
        if (this != &other) {
            Entity::operator=(other);
            range = other.range;
            amount = other.amount;
            lastAttackTime = other.lastAttackTime;
            attackReady = other.attackReady;
            life = other.life;
        }
        return *this;
    }

    // Check if target is in range
    bool Enemy::IsInRange(int x, int y) {
        int dx = GetDX() - x;
        int dy = GetDY() - y;
        // Calculate distance using Pythagorean theorem
        double distance = sqrt(dx * dx + dy * dy);
        // Check if distance is within the attack range
        return distance <= range;
    }

    // Reset the attack cooldown
    void Enemy::ResetAttackCooldown() {
        // Set the last attack time to the current time
        lastAttackTime = SDL_GetTicks();
        attackReady = false;
    }

    // Update cooldown status
    void Enemy::UpdateCooldown() {
        // If not ready to attack, check if cooldown has expired
        if (!attackReady) {
            // Get the current time
            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - lastAttackTime >= ATTACK_COOLDOWN) {
                attackReady = true;
            }
        }
    }

    // Movement method
    void Enemy::MoveTowards(int x, int y, float speed) {
        // Calculate direction to target
        float dx = x - GetDX();
        float dy = y - GetDY();
        // Calculate distance
        float distance = sqrt(dx*dx + dy*dy);
        // Only move if not already at the target's position
        if (distance > 0) {
            // Normalize direction vector
            dx /= distance;
            dy /= distance;
            // Move toward target at a fixed speed
            float moveSpeed = speed;
            // Calculate new position
            // Use static_cast to convert float to int for position
            int newX = GetDX() + static_cast<int>(dx * moveSpeed);
            int newY = GetDY() + static_cast<int>(dy * moveSpeed);
            // Update position
            SetDest(newX, newY, GetDW(), GetDH());
        }
    }

    // Attack method
    void Enemy::Attack(Player &target, int amount) {
        // Only attack if cooldown has expired
        if (!CanAttack()) {
            return;
        }
        // Check if target is in range
        if (IsInRange(target.GetDX(), target.GetDY())) {
            // Deal damage
            target.TakeDamage(amount);
            // Reset cooldown
            ResetAttackCooldown();
        }
    }

    // Take damage method
    void Enemy::TakeDamage(int amount) {
        // Reduce health by amount
        int newHealth = GetHealth() - amount;
        // Ensure health does not go below zero
        SetHealth(newHealth > 0 ? newHealth : 0);
    }

    // Overloading + operator
    int operator+(const Enemy& lhs, const Enemy& rhs) {
        return lhs.GetHealth() + rhs.GetHealth();
    }
}