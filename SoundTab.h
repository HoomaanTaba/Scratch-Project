//
// Created by Fazel on 2/15/2026.
//

#ifndef SCRATCH_SOUNDTAB_H
#define SCRATCH_SOUNDTAB_H

#include <SDL2/SDL.h>
#include "SDLInclude.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <SDL2/SDL_audio.h>

#define MAX_SOUNDS 100

static Mix_Chunk* SM_sounds[MAX_SOUNDS];
static std::string SM_names[MAX_SOUNDS];
static int SM_count = 0;

static int SM_volume = MIX_MAX_VOLUME;
static bool SM_muted = false;

static std::string SM_message;

inline bool SM_Init() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        SM_message = "Audio Init Failed";
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        SM_message = "Mixer Init Failed";
        return false;
    }

    srand((unsigned int)time(NULL));
    SM_message = "Sound System Ready";
    return true;
}

inline void SM_AddSound(const std::string& path) {
    if (SM_count >= MAX_SOUNDS) {
        SM_message = "Sound Limit Reached";
        return;
    }

    Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());

    if (!chunk) {
        SM_message = "Failed To Load Sound";
        return;
    }

    SM_sounds[SM_count] = chunk;
    SM_names[SM_count] = path;
    SM_count++;

    SM_message = "Sound Added Successfully";
}

inline void SM_Play(int index) {
    if (index < 0 || index >= SM_count) {
        SM_message = "Invalid Sound Index";
        return;
    }

    if (!SM_muted)
        Mix_PlayChannel(-1, SM_sounds[index], 0);

    SM_message = "Sound Played";
}

inline void SM_PlayRandom () {
    if (SM_count == 0) {
        SM_message = "No Sounds Available";
        return;
    }

    int index = rand() % SM_count;
    SM_Play(index);
}

inline void SM_ToggleMute() {
    SM_muted = !SM_muted;

    if (SM_muted) {
        Mix_Volume(-1, 0);
        SM_message = "Muted";
    }
    else {
        Mix_Volume(-1, SM_volume);
        SM_message = "Unmuted";
    }
}

inline void SM_SetVolume(int percent) {
    if (percent > 100)
        percent = 100;
    else if (percent < 0)
        percent = 0;

    SM_volume = (percent * MIX_MAX_VOLUME) / 100;

    if (!SM_muted)
        Mix_Volume(-1, SM_volume);

    SM_message = "Volume Updated";
}

inline std::string SM_GetMessage() {
    return SM_message;
}

inline void SM_Cleanup() {
    for (int i = 0; i < SM_count; i++)
        Mix_FreeChunk(SM_sounds[i]);

    Mix_CloseAudio();
}
#endif //SCRATCH_SOUNDTAB_H
