#include "menu.h"



void Menu::TogglePause() {
    isPaused = !isPaused;
}

bool Menu::IsPaused() const {
    return isPaused;
}