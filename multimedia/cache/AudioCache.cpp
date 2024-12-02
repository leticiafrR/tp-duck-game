#include "AudioCache.h"

map<string, Chunk> AudioCache::sfxCache;
map<string, Music> AudioCache::musicCache;

Chunk& AudioCache::GetSFXData(const string& filename) {
    auto it = sfxCache.find(filename);
    if (it != sfxCache.end()) {
        return it->second;
    }

    sfxCache.emplace(filename, Chunk(AUDIO_PATH + filename));
    return sfxCache.at(filename);
}

Music& AudioCache::GetMusicData(const string& filename) {
    auto it = musicCache.find(filename);
    if (it != musicCache.end()) {
        return it->second;
    }

    musicCache.emplace(filename, Music(AUDIO_PATH + filename));
    return musicCache.at(filename);
}

const Chunk& AudioCache::GetAudioSFXData(const string& filename) {
    if (sfxMapCache.contains(filename)) {
        return sfxMapCache.at(filename);
    }

    sfxMapCache.emplace(filename, Chunk(AUDIO_PATH + filename));
    return sfxMapCache.at(filename);
}

const Music& AudioCache::GetAudioMusicData(const string& filename) {
    if (musicMapCache.contains(filename)) {
        return musicMapCache.at(filename);
    }

    musicMapCache.emplace(filename, Music(AUDIO_PATH + filename));
    return musicMapCache.at(filename);
}


void AudioCache::Clear() {
    sfxCache.clear();
    musicCache.clear();
}
