#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include <string>
#include <unordered_map>

#include <SDL2pp/SDL2pp.hh>

#include "data/snapshot.h"
#include "multimedia/Camera.h"
#include "multimedia/cache/AudioCache.h"

using std::string;
using std::unordered_map;
using namespace SDL2pp;  // NOLINT

class AudioManager {
private:
    const int MAX_CHANELS = 20;
    Mixer mixer;
    AudioCache audioCache;

public:
    AudioManager();
    ~AudioManager();

    void PlaySFX(const string& filename);

    void PlayMusic(const string& filename);

    void StopMusic();

    // Remove copy
    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;
};

#endif
