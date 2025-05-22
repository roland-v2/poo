#pragma once

#include "object.h"
#include "enemy.h"
#include <vector>

namespace OOP_Game {
    // Key class inherits from Object
    class Key : public Object {
    public:
        // Constructor
        Key();

        // Check if all enemies are dead
        bool AllEnemiesDead(const vector<Enemy>& enemies) const;

        // Spawn key methods
        void Despawn() { m_spawned = false; }
        void SetSpawn(bool spawn) { m_spawned = spawn; }
        bool GetSpawn() const { return m_spawned; }

        // Picked up methods
        void SetPickedUp(bool pickedUp) { m_is_picked_up = pickedUp; }
        bool GetPickedUp() const { return m_is_picked_up; }

    private:
        // Key attributes
        bool m_spawned;
        bool m_is_picked_up;
    };
}