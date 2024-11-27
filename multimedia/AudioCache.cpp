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

void AudioCache::Clear() {
    sfxCache.clear();
    musicCache.clear();
}
