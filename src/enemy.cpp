#include "include/enemy.h"
#include "include/player.h"
#include <cmath>
#include "libs/SDL2/include/SDL.h"

namespace OOP_Game {
    // Default initialization of enemy attributes
    Enemy::Enemy() :
        m_range(25),
        m_amount(10),
        m_attack_ready(true),
        m_life(50),
        m_last_attack_time(0)
    {
        SetHealth(50);
        SetMaxHealth(50);
    }

    // Implement copy constructor
    // This constructor initializes the enemy with the same attributes as another enemy at creation
    Enemy::Enemy(const Enemy& other) : Entity(other) {
        m_range = other.m_range;
        m_amount = other.m_amount;
        m_last_attack_time = other.m_last_attack_time;
        m_attack_ready = other.m_attack_ready;
        m_life = other.m_life;
    }

    // Implement copy assignment operator
    // This operator assigns the attributes of one enemy to another after creation
    Enemy& Enemy::operator=(const Enemy& other) {
        if (this != &other) {
            Entity::operator=(other);
            m_range = other.m_range;
            m_amount = other.m_amount;
            m_last_attack_time = other.m_last_attack_time;
            m_attack_ready = other.m_attack_ready;
            m_life = other.m_life;
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
        return distance <= m_range;
    }

    // Reset the attack cooldown
    void Enemy::ResetAttackCooldown() {
        // Set the last attack time to the current time
        m_last_attack_time = SDL_GetTicks();
        m_attack_ready = false;
    }

    // Update cooldown status
    void Enemy::UpdateCooldown() {
        // If not ready to attack, check if cooldown has expired
        if (!m_attack_ready) {
            // Get the current time
            Uint32 current_time = SDL_GetTicks();
            if (current_time - m_last_attack_time >= m_attack_cooldown) {
                m_attack_ready = true;
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
            float move_speed = speed;
            // Calculate new position
            // Use static_cast to convert float to int for position
            int new_x = GetDX() + static_cast<int>(dx * move_speed);
            int new_y = GetDY() + static_cast<int>(dy * move_speed);
            // Update position
            SetDest(new_x, new_y, GetDW(), GetDH());
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
        int new_health = GetHealth() - amount;
        // Ensure health does not go below zero
        SetHealth(new_health > 0 ? new_health : 0);
    }

    // Overloading + operator
    int operator+(const Enemy& enemy1_health, const Enemy& enemy2_health) {
        return enemy1_health.GetHealth() + enemy2_health.GetHealth();
    }
}