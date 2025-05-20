#include "enemy.h"
#include "player.h" // Include player.h in the implementation file
#include <cmath>

Enemy::Enemy() :
    range(25),
    amount(10),
    lastAttackTime(0),
    attackReady(true),
    life(50)
{
    SetHealth(50);
    SetMaxHealth(50);
}

Enemy::~Enemy() {
    // Cleanup
}

// Implement copy constructor
Enemy::Enemy(const Enemy& other) : Entity(other) {
    range = other.range;
    amount = other.amount;
    lastAttackTime = other.lastAttackTime;
    attackReady = other.attackReady;
    life = other.life;
}

// Implement copy assignment operator
Enemy& Enemy::operator=(const Enemy& other) {
    if (this != &other) {
        Entity::operator=(other);  // Call base class assignment
        range = other.range;
        amount = other.amount;
        lastAttackTime = other.lastAttackTime;
        attackReady = other.attackReady;
        life = other.life;
    }
    return *this;
}

bool Enemy::IsInRange(int x, int y) {
    int dx = GetDX() - x;
    int dy = GetDY() - y;
    double distance = sqrt(dx * dx + dy * dy);
    
    return distance <= range;
}

// Update to use ATTACK_COOLDOWN instead of attackCooldown
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
        if (currentTime - lastAttackTime >= ATTACK_COOLDOWN) {
            attackReady = true;
        }
    }
}

// Add implementation for any remaining methods
void Enemy::MoveTowards(int x, int y) {
    // Calculate direction to player
    float dx = x - GetDX();
    float dy = y - GetDY();
    
    // Calculate distance
    float distance = sqrt(dx*dx + dy*dy);
    
    // Only move if not already at the player's position
    if (distance > 0) {
        // Normalize direction vector
        dx /= distance;
        dy /= distance;
        
        // Move toward player at a fixed speed
        float moveSpeed = 1.5f;
        int newX = GetDX() + static_cast<int>(dx * moveSpeed);
        int newY = GetDY() + static_cast<int>(dy * moveSpeed);
        
        // Update position
        SetDest(newX, newY, GetDW(), GetDH());
    }
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

void Enemy::TakeDamageE(int amount) {
    int newHealth = GetHealth() - amount;
    SetHealth(newHealth > 0 ? newHealth : 0);
}