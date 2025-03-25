#pragma once

class Monster 
{
public:
    Monster(int hp);
    int GetHp();
    void TakeDamage(int amount);
private:
    int mHp;
};