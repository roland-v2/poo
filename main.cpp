// Priect POO - Boldesco Roland

#include "monster.h"
#include <iostream>

int main() {
    Monster monster(100);
    monster.TakeDamage(60);
    std::cout << monster.GetHp() << std::endl;
    return 0;
}