#include "include/key.h" 

namespace OOP_Game {
    // Constructor
    Key::Key() : m_spawned(false), m_is_picked_up(false) {}

    // Check if all enemies are dead
    bool Key::AllEnemiesDead(const std::vector<Enemy>& enemies) const {
        // Check if the enemies vector is empty
        if (enemies.empty()) { return true;}
        return false;
    }
}