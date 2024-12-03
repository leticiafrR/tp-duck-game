#include "AudioManager.h"

#include "multimedia/cache/AudioCache.h"

AudioManager::AudioManager(AudioCache& audioCache):
        audioCache(audioCache), mixer(audioCache.GetMixer()) {}

AudioManager::~AudioManager() = default;

void AudioManager::PlayButtonSFX() { PlaySFX(BUTTON_SFX_FILE); }

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
