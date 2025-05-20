#pragma once

#include </opt/homebrew/include/SDL2/SDL.h>
#include </opt/homebrew/include/SDL2/SDL_image.h>
#include </opt/homebrew/include/SDL2/SDL_ttf.h>
#include </opt/homebrew/include/SDL2/SDL_mixer.h>
#include <iostream>

class Menu {
public:
    
    void TogglePause();
    
    // Check if game is paused
    bool IsPaused() const;
    
private:
    bool isPaused;
};
