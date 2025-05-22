#include "include/audio.h"

namespace OOP_Game {
    // Cleanup for audio
    Audio::~Audio() {
        SDL_CloseAudioDevice(m_device_ID);
        SDL_FreeWAV(m_wave_buffer);
    }

    // Load a WAV file
    void Audio::Load(const char *filename) {
        SDL_LoadWAV(filename, &m_wave_spec, &m_wave_buffer, &m_wave_length);
        // Device ID is the identifier for the audio device
        m_device_ID = SDL_OpenAudioDevice(NULL, 0, &m_wave_spec, NULL, 0);
    }

    // Play the loaded WAV file
    void Audio::Play() {
        SDL_QueueAudio(m_device_ID, m_wave_buffer, m_wave_length);
        SDL_PauseAudioDevice(m_device_ID, 0);
    }
}