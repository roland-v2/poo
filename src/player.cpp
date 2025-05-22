#include "include/player.h"

namespace OOP_Game {
    // Initializes default player attributes
    Player::Player() : m_score(0), m_lives(3), m_range_player(100), m_damage(15) {
        SetHealth(100);
        SetMaxHealth(100);
    }

    // Lives method
    void Player::LoseLife() {
        // Number of lives drops by one
        m_lives--;
        // Check if player is still alive
        if (m_lives > 0) {
            // Sets player's current life to max
            SetHealth(GetMaxHealth());
        }
    }

    // Health/damage methods
    void Player::TakeDamage(int amount) {
        // Drops health by amount
        SetHealth(GetHealth() - amount);
        // Check if health is below zero
        if (GetHealth() <= 0) {
            // Don't go below zero
            SetHealth(0);
            // Go to next life  
            LoseLife();
        }
    }

    void Player::AttackEnemy(Enemy &target, int amount) {
        // If the enemy is in range, deal damage
        if (EnemyIsInRange(target.GetDX(), target.GetDY())) {
            target.TakeDamage(amount);
        }
    }

    void Player::AttackBossEnemy(Enemy &target, int amount) {
        // If the boss enemy is in range, deal damage
        if (EnemyIsInRange(target.GetDX(), target.GetDY())) {
            target.TakeDamage(amount);
        }
    }

    // Function 
    void Player::AttackBossEnemy(Enemy &target) {
        // If the boss enemy is in range, deal damage
        if (EnemyIsInRange(target.GetDX(), target.GetDY())) {
            target.TakeDamage(this->GetDamage());
        }
    }

    // Range method
    bool Player::EnemyIsInRange(int x, int y) {
        int dx = GetDX() - x;
        int dy = GetDY() - y;
        // Calculate the distance to the enemy
        double distance = sqrt(dx * dx + dy * dy);
        // Check if the distance is within the player's range
        return distance <= m_range_player;
    }

    //overloading << operator
    std::ostream& operator<<(std::ostream& os, const Player& player) {
        os << "Player Stats:\n";
        os << "Score: " << player.GetScore() << "\n";
        os << "Lives: " << player.GetLives() << "\n";
        os << "Health: " << player.GetHealth() << "/" << player.GetMaxHealth() << "\n";
        os << "Damage: " << player.GetDamage() << "\n";
        os << "Range: " << player.GetRange() << "\n";
        return os;
    }
}