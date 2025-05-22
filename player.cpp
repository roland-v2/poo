#include "player.h"

namespace OOPGame {
    // Initializes default player attributes
    Player::Player() : score(0), lives(3), rangePlayer(100), damage(15) {
        SetHealth(100);
        SetMaxHealth(100);
    }

    // Lives method
    void Player::LoseLife() {
        // Number of lives drops by one
        lives--;
        // Check if player is still alive
        if (lives > 0) {
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
        return distance <= rangePlayer;
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