#include "player.h"

Player::Player() : score(0), lives(3) {
    SetHealth(100);
    SetMaxHealth(100);
}

// Score methods
void Player::AddScore(int points) {
    score += points;
}

void Player::ResetScore() {
    score = 0;
}

int Player::GetScore() const {
    return score;
}

// Lives methods
void Player::SetLives(int lives) {
    this->lives = lives;
}

int Player::GetLives() const {
    return lives;
}

void Player::LoseLife() {
    lives--;
    if (lives > 0) {
        // Reset health when losing a life but still alive
        SetHealth(GetMaxHealth());
    }
}

bool Player::IsAlive() const {
    return lives > 0;
}

// Health methods
void Player::TakeDamage(int amount) {
    SetHealth(GetHealth() - amount);
    
    // Check if health is depleted
    if (GetHealth() <= 0) {
        SetHealth(0); // Don't go below zero
        LoseLife();
    }
}