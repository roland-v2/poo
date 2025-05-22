#include "bossEnemy.h"

// Default boss initialization
BossEnemy::BossEnemy() {
    SetHealth(500);
    SetMaxHealth(500);
    SetRange(100);
}

// EngGame method to play the game over sound
void BossEnemy::EndGame(Audio& audio) {
    // Load and play the game over sound
    audio.Load("res/gameOver.wav");
    audio.Play();
}