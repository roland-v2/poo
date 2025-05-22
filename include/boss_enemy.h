#pragma once

#include "enemy.h"
#include "audio.h"

namespace OOP_Game {
    // BossEnemy class inherits from Enemy
    class BossEnemy : public Enemy {
    public:
        // Constructor
        BossEnemy();

        // Damage method
        void TakeDamage(int amount) override;

        // Play the end game sound
        void EndGame(Audio& audio);
    };
}