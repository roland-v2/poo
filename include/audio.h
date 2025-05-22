#pragma once

#include "libs/SDL2/include/SDL.h"
#include "libs/SDL2/include/SDL_mixer.h"
#include <iostream>

namespace OOPGame {
    class Audio {
    public:
        // Destructor
        ~Audio();

        // Load a WAV file
        void Load(const char *filename);

        // Play the loaded WAV file
        void Play();
    private:
        // SDL audio specifications
        SDL_AudioSpec waveSpec;
        Uint32 waveLength;
        Uint8 *waveBuffer;
        SDL_AudioDeviceID deviceID;
    };
}