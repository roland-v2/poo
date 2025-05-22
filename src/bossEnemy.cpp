#include "include/bossEnemy.h"

namespace OOPGame {
    // Default boss initialization
    BossEnemy::BossEnemy() {
        SetHealth(500);
        SetMaxHealth(500);
        SetRange(100);
    }

    // Damage method to handle boss damage
    void BossEnemy::TakeDamage(int amount) {
        // Reduce health by amount
        int newHealth = GetHealth() - amount;
        // Ensure health does not go below zero
        SetHealth(newHealth > 0 ? newHealth : 0);
    }

    // EndGame method to play the game over sound
    void BossEnemy::EndGame(Audio& audio) {
        // Play the game over sound
        audio.Play();
    }
}