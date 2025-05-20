#include "enemy.h"
#include <cmath>

Enemy::Enemy() :
    range(25),
    amount(10),
    lastAttackTime(0),
    attackReady(true)
{
    // Initialize enemy
}

Enemy::~Enemy() {
    // Cleanup
}

bool Enemy::IsInRange(int x, int y) {
    int dx = GetDX() - x;
    int dy = GetDY() - y;
    double distance = sqrt(dx * dx + dy * dy);
    
    return distance <= range;
}

void Enemy::Attack(Player &target, int amount) {
    // Only attack if cooldown has expired
    if (!CanAttack()) {
        return;
    }
    
    if (IsInRange(target.GetDX(), target.GetDY())) {
        // Deal damage
        target.TakeDamage(amount);
        
        // Reset cooldown
        ResetAttackCooldown();
        
        // Debug output
        std::cout << "Enemy attacked! Player health: " << target.GetHealth() << std::endl;
    }
}

bool Enemy::CanAttack() const {
    return attackReady;
}

void Enemy::ResetAttackCooldown() {
    lastAttackTime = SDL_GetTicks();
    attackReady = false;
}

void Enemy::UpdateCooldown() {
    // If not ready to attack, check if cooldown has expired
    if (!attackReady) {
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastAttackTime >= attackCooldown) {
            attackReady = true;
        }
    }
}

void Enemy::MoveTowards(int x, int y) {
    // Move towards the player
    float dx = x - GetDX();
    float dy = y - GetDY();
    float distance = sqrt(dx * dx + dy * dy);
    
    if (distance > 0) {
        dx /= distance;
        dy /= distance;
        
        SetDest(GetDX() + dx * 2, GetDY() + dy * 2); // Move at a speed of 2 units
    }
}