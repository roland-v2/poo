#pragma once

#include "enemy.h"
#include "audio.h"

// BossEnemy class inherits from Enemy
class BossEnemy : public Enemy {
public:
    // Constructor
    BossEnemy();

    // Play the end game sound
    void EndGame(Audio& audio);
};