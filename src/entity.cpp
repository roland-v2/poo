#include "include/entity.h"

namespace OOP_Game {
    // Constructor
    Entity::Entity() {}
    Entity::~Entity() {}

    // Animations are based on a png file with multiple frames
    // The cycle is a struct that contains the row, width, height, amount of frames and speed of the animation
    // The CreateCycle function creates a cycle and adds it to the animations vector
    int Entity::CreateCycle(int r, int w, int h, int amount, int speed) {
        // Create cycle
        m_cycle temp;
        temp.row = r - 1;
        temp.w = w;
        temp.h = h;
        temp.amount = amount;
        temp.speed = speed;
        temp.tick = 0;
        // Add cycle to animations vector
        animations.push_back(temp);
        return animations.size() - 1;
    }

    // The UpdateAnimation function updates the animation by changing the source rectangle of the entity
    void Entity::UpdateAnimation() {
        // Set the source rectangle to the current animation
        SetSrc(animations[m_curr_anim].w * animations[m_curr_anim].tick, animations[m_curr_anim].row * animations[m_curr_anim].h, animations[m_curr_anim].w, animations[m_curr_anim].h);
        // If the animation is paused, do not update the tick
        // If the animation is not paused, update the tick
        if(m_begin > animations[m_curr_anim].speed) {
            animations[m_curr_anim].tick++;
            m_begin = 0;
        }
        m_begin++;
        // If the tick is greater than the amount of frames, reset it to 0. Take animation to frame 1 again
        if(animations[m_curr_anim].tick >= animations[m_curr_anim].amount) {animations[m_curr_anim].tick = 0;}
    }

    // Damage method to handle damage
    void Entity::TakeDamage(int amount) {
        // Reduce health by amount
        int new_health = GetHealth() - amount;
        // Ensure health does not go below zero
        SetHealth(new_health > 0 ? new_health : 0);
    }
}