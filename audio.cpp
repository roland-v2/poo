#include "audio.h"

Audio::~Audio() {
    SDL_CloseAudioDevice(deviceID);
    SDL_FreeWAV(waveBuffer);
}

void Audio::Load(const char *filename) {
    SDL_LoadWAV (filename, &waveSpec, &waveBuffer, &waveLength);
    deviceID = SDL_OpenAudioDevice(NULL, 0, &waveSpec, NULL, 0);
}

void Audio::Play() {
    SDL_QueueAudio(deviceID, waveBuffer, waveLength);
    SDL_PauseAudioDevice(deviceID, 0);
}