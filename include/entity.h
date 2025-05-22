#pragma once

#include "object.h"
#include <vector>

namespace OOPGame {
    // Entity class inherits from Object
    class Entity : public Object {
    public:
        Entity();
        virtual ~Entity();
        // Health methods
        void SetHealth(int h) {health = h;}
        void SetMaxHealth(int h) {maxHealth = h;}
        int GetHealth() const {return health;}
        int GetMaxHealth() const {return maxHealth;}
        // Damage method - class polymorphism
        virtual void TakeDamage(int amount);

        // Animation methods
        int CreateCycle(int r, int w, int h, int amount, int speed);
        void SetCurrAnim(int c) {begin = 0; currAnim = c;}
        int GetCurrAnim() const {return currAnim;}
        void UpdateAnimation();
    private:
        // Health attributes
        int health, maxHealth;

        // Animation attributes
        struct cycle {
            int row;
            int w;
            int h;
            int amount;
            int speed;
            int tick;
        };
        vector <cycle> animations;
        int currAnim;
        int begin;
    };
}