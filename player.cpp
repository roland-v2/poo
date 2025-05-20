#include "player.h"
#include "enemy.h" // Include enemy.h in the implementation file

Player::Player() : score(0), lives(3), rangePlayer(100) {
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

void Player::AttackEnemy(Enemy &target, int amount) {
    if (EnemyIsInRange(target.GetDX(), target.GetDY())) {
        target.TakeDamageE(amount);
    }
}

bool Player::EnemyIsInRange(int x, int y) {
    int dx = GetDX() - x;
    int dy = GetDY() - y;
    double distance = sqrt(dx * dx + dy * dy);
    
    return distance <= rangePlayer;
}