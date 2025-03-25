#include "monster.h"

Monster::Monster(int hp) {
    mHp = hp;
}

int Monster::GetHp() {
    return mHp;
}

void Monster::TakeDamage(int amount) {
    mHp -= amount;
    if(mHp < 0) {
        mHp = 0;
    }
}