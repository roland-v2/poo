#pragma once

#include "object.h"
#include <vector>

namespace OOP_Game {
    // Entity class inherits from Object
    class Entity : public Object {
    public:
        Entity();
        virtual ~Entity();
        // Health methods
        void SetHealth(int h) {m_health = h;}
        void SetMaxHealth(int h) {m_max_health = h;}
        int GetHealth() const {return m_health;}
        int GetMaxHealth() const {return m_max_health;}
        // Damage method - class polymorphism
        virtual void TakeDamage(int amount);

        // Animation methods
        int CreateCycle(int r, int w, int h, int amount, int speed);
        void SetCurrAnim(int c) {m_begin = 0; m_curr_anim = c;}
        int GetCurrAnim() const {return m_curr_anim;}
        void UpdateAnimation();
    private:
        // Health attributes
        int m_health, m_max_health;

        // Animation attributes
        struct m_cycle {
            int row;
            int w;
            int h;
            int amount;
            int speed;
            int tick;
        };
        vector <m_cycle> animations;
        int m_curr_anim;
        int m_begin;
    };
}