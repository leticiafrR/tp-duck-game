#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include <string>
#include <unordered_map>

#include <SDL2pp/SDL2pp.hh>

#include "data/snapshot.h"

#include "AudioCache.h"
#include "Camera.h"
#include "GraphicUI.h"

using std::string;
using std::unordered_map;
using namespace SDL2pp;  // NOLINT

class AudioManager {
private:
    const int MAX_CHANELS = 20;
    Mixer mixer;
    AudioManager(): mixer(44100, MIX_DEFAULT_FORMAT, 2, 2048) {
        mixer.AllocateChannels(MAX_CHANELS);
    }

    const unordered_map<TypeProjectile, string> bulletSFX = {
            {TypeProjectile::BULLET, "bulletSFX.wav"},
            {TypeProjectile::LASER, "laserSFX.mp3"},
            {TypeProjectile::FRAGMENT, ""},
            {TypeProjectile::BANANA, ""}};


public:
    static AudioManager& GetInstance() {
        static AudioManager Instance;
        return Instance;
    }

    void PlayShootSFX(TypeProjectile type = TypeProjectile::BULLET) { PlaySFX(bulletSFX.at(type)); }
    void PlayDamagedSFX() { PlaySFX("damagedSFX.mp3"); }
    void PlayButtonSFX() { PlaySFX("buttonSFX.mp3"); }

    void PlayGameMusic() { PlayMusic("bgMusic.mp3"); }

    void PlaySFX(const string& filename) {
        Chunk& audio = AudioCache::GetSFXData(filename);
        if (mixer.IsChannelPlaying(-1) == MAX_CHANELS) {
            return;
        }
        mixer.PlayChannel(-1, audio, 0);
    }

    void PlayMusic(const string& filename) {
        Music& audio = AudioCache::GetMusicData(filename);
        mixer.PlayMusic(audio, -1);
    }

    void StopMusic() { mixer.PauseMusic(); }

    // Remove copy
    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;

    ~AudioManager() = default;
};

#endif
