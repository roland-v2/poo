#pragma once

#include "object.h"
#include "enemy.h"
#include <vector>

// Key class inherits from Object
class Key : public Object {
public:
    // Constructor
    Key();

    // Check if all enemies are dead
    bool AllEnemiesDead(const vector<Enemy>& enemies) const;

    // Spawn key methods
    void Despawn() { spawned = false; }
    void SetSpawn(bool spawn) { spawned = spawn; }
    bool GetSpawn() const { return spawned; }

    // Picked up methods
    void SetPickedUp(bool pickedUp) { isPickedUp = pickedUp; }
    bool GetPickedUp() const { return isPickedUp; }

private:
    // Key attributes
    bool spawned;
    bool isPickedUp;
};