#include "audio.h"

namespace OOPGame {
    // Cleanup for audio
    Audio::~Audio() {
        SDL_CloseAudioDevice(deviceID);
        SDL_FreeWAV(waveBuffer);
    }

    // Load a WAV file
    void Audio::Load(const char *filename) {
        SDL_LoadWAV(filename, &waveSpec, &waveBuffer, &waveLength);
        // Device ID is the identifier for the audio device
        deviceID = SDL_OpenAudioDevice(NULL, 0, &waveSpec, NULL, 0);
    }

    // Play the loaded WAV file
    void Audio::Play() {
        SDL_QueueAudio(deviceID, waveBuffer, waveLength);
        SDL_PauseAudioDevice(deviceID, 0);
    }
}