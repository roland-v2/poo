#include "key.h"

// Constructor
Key::Key() : spawned(false), isPickedUp(false) {}

// Check if all enemies are dead
bool Key::AllEnemiesDead(const std::vector<Enemy>& enemies) const {
    // Check if the enemies vector is empty
    if (enemies.empty()) { return true;}
    return false;
}