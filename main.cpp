// Proiect POO - Boldesco Roland

#include "monster.h"
#include </opt/homebrew/include/SDL2/SDL.h>
#include </opt/homebrew/include/SDL2/SDL_image.h>
#include </opt/homebrew/include/SDL2/SDL_ttf.h>
#include </opt/homebrew/include/SDL2/SDL_mixer.h>
#include <iostream>

int main() {
    Monster monster(100);
    monster.TakeDamage(60);
    std::cout << monster.GetHp() << std::endl;
    return 0;
}