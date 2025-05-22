#pragma once

#include "libs/SDL2/include/SDL.h"
#include "libs/SDL2/include/SDL_mixer.h"
#include <iostream>

namespace OOP_Game {
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
        SDL_AudioSpec m_wave_spec;
        Uint32 m_wave_length;
        Uint8 *m_wave_buffer;
        SDL_AudioDeviceID m_device_ID;
    };
}