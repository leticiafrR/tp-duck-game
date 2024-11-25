#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include <string>
#include <unordered_map>

#include <SDL2pp/SDL2pp.hh>

#include "AudioCache.h"
#include "Camera.h"
#include "GraphicUI.h"

using std::string;
using std::unordered_map;
using namespace SDL2pp;  // NOLINT

class AudioManager {
private:
    Mixer mixer;
    AudioManager(): mixer(44100, MIX_DEFAULT_FORMAT, 2, 2048) {}

    const unordered_map<TypeProjectile, string> bulletSFX = {
            {TypeProjectile::Bullet, "bulletSFX.wav"},
            {TypeProjectile::RayoLaser, "laserSFX.mp3"},
            {TypeProjectile::GranadaFragment, ""},
            {TypeProjectile::Banana, ""}};


public:
    static AudioManager& GetInstance() {
        static AudioManager Instance;
        return Instance;
    }

    void PlayShootSFX(TypeProjectile type = TypeProjectile::Bullet) { PlaySFX(bulletSFX.at(type)); }
    void PlayDamagedSFX() { PlaySFX("damagedSFX.mp3"); }
    void PlayButtonSFX() { PlaySFX("buttonSFX.mp3"); }

    void PlayGameMusic() { PlayMusic("bgMusic.mp3"); }

    void PlaySFX(const string& filename) {
        Chunk& audio = AudioCache::GetSFXData(filename);
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
