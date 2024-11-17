#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include <string>

#include <SDL2pp/SDL2pp.hh>

#include "AudioCache.h"
#include "Camera.h"
#include "GraphicUI.h"

using std::string;
using namespace SDL2pp;  // NOLINT

class AudioManager {
private:
    Mixer mixer;
    AudioManager(): mixer(44100, MIX_DEFAULT_FORMAT, 2, 2048) {}

public:
    static AudioManager& GetInstance() {
        static AudioManager Instance;
        return Instance;
    }

    void PlayShoot() { PlaySFX("instant_boom.wav"); }

    void PlaySFX(const string& filename) {
        Chunk& audio = AudioCache::GetData(filename);
        mixer.PlayChannel(-1, audio, 0);
    }

    // Remove copy
    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;

    ~AudioManager() = default;
};

#endif
