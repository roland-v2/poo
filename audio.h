#pragma once

#include </opt/homebrew/include/SDL2/SDL.h>
#include </opt/homebrew/include/SDL2/SDL_image.h>
#include </opt/homebrew/include/SDL2/SDL_ttf.h>
#include </opt/homebrew/include/SDL2/SDL_mixer.h>
#include <iostream>

class Audio {
public:
    Audio();
    ~Audio();
    void Load(const char *filename);
    void Play();
private:
    SDL_AudioSpec waveSpec;
    Uint32 waveLength;
    Uint8 *waveBuffer;
    SDL_AudioDeviceID deviceID;
};