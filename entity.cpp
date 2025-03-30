#include "entity.h"

int Entity::createCycle(int r, int w, int h, int amount, int speed) {
    cycle temp;
    temp.row = r - 1;
    temp.w = w;
    temp.h = h;
    temp.amount = amount;
    temp.speed = speed;
    temp.tick = 0;
    animations.push_back(temp);
    return animations.size() - 1;
}
void Entity::updateAnimation() {
    setSrc(animations[currAnim].w * animations[currAnim].tick, animations[currAnim].row * animations[currAnim].h, animations[currAnim].w, animations[currAnim].h);
    if(begin > animations[currAnim].speed) {animations[currAnim].tick++; begin = 0;}
    begin++;
    if(animations[currAnim].tick >= animations[currAnim].amount) {animations[currAnim].tick = 0;}
}