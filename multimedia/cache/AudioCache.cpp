#include "AudioCache.h"

AudioCache::AudioCache(): audioMixer(44100, MIX_DEFAULT_FORMAT, 2, 2048) {
    audioMixer.AllocateChannels(MAX_CHANELS);
}

Mixer& AudioCache::GetMixer() { return audioMixer; }


Chunk& AudioCache::GetAudioSFXData(const string& filename) {
    if (sfxMapCache.contains(filename)) {
        return sfxMapCache.at(filename);
    }

    sfxMapCache.emplace(filename, Chunk(AUDIO_PATH + filename));
    return sfxMapCache.at(filename);
}

Music& AudioCache::GetAudioMusicData(const string& filename) {
    if (musicMapCache.contains(filename)) {
        return musicMapCache.at(filename);
    }

    musicMapCache.emplace(filename, Music(AUDIO_PATH + filename));
    return musicMapCache.at(filename);
}
