#include "AudioManager.h"

AudioManager::AudioManager(): mixer(44100, MIX_DEFAULT_FORMAT, 2, 2048) {
    mixer.AllocateChannels(MAX_CHANELS);
}

AudioManager::~AudioManager() = default;

void AudioManager::PlaySFX(const string& filename) {
    const Chunk& audio = audioCache.GetAudioSFXData(filename);
    if (mixer.IsChannelPlaying(-1) == MAX_CHANELS) {
        return;
    }
    mixer.PlayChannel(-1, audio, 0);
}

void AudioManager::PlayMusic(const string& filename) {
    const Music& audio = audioCache.GetAudioMusicData(filename);
    mixer.PlayMusic(audio, -1);
}

void AudioManager::StopMusic() { mixer.PauseMusic(); }
