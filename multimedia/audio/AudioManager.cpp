#include "AudioManager.h"

AudioManager::AudioManager(): mixer(44100, MIX_DEFAULT_FORMAT, 2, 2048) {
    mixer.AllocateChannels(MAX_CHANELS);
}

AudioManager::~AudioManager() = default;

AudioManager& AudioManager::GetInstance() {
    static AudioManager Instance;
    return Instance;
}

void AudioManager::PlayShootSFX(TypeProjectile type) {
    PlaySFX(bulletSFX.contains(type) ? bulletSFX.at(type) : bulletSFX.at(TypeProjectile::BULLET));
}

void AudioManager::PlayCuackSFX() { PlaySFX("cuackSFX.mp3"); }
void AudioManager::PlayDamagedSFX() { PlaySFX("damagedSFX.mp3"); }
void AudioManager::PlayButtonSFX() { PlaySFX("buttonSFX.mp3"); }

void AudioManager::PlayGameMusic() { PlayMusic("bgMusic.mp3"); }

void AudioManager::PlaySFX(const string& filename) {
    Chunk& audio = AudioCache::GetSFXData(filename);
    if (mixer.IsChannelPlaying(-1) == MAX_CHANELS) {
        return;
    }
    mixer.PlayChannel(-1, audio, 0);
}

void AudioManager::PlayMusic(const string& filename) {
    Music& audio = AudioCache::GetMusicData(filename);
    mixer.PlayMusic(audio, -1);
}

void AudioManager::StopMusic() { mixer.PauseMusic(); }
