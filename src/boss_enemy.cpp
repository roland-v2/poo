#include "include/boss_enemy.h"

namespace OOP_Game {
    // Default boss initialization
    BossEnemy::BossEnemy() {
        SetHealth(500);
        SetMaxHealth(500);
        SetRange(100);
    }

    // Damage method to handle boss damage
    void BossEnemy::TakeDamage(int amount) {
        // Reduce health by amount
        int new_health = GetHealth() - amount;
        // Ensure health does not go below zero
        SetHealth(new_health > 0 ? new_health : 0);
    }

    // EndGame method to play the game over sound
    void BossEnemy::EndGame(Audio& audio) {
        // Play the game over sound
        audio.Play();
    }
}