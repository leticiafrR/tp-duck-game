#ifndef AUDIO_CACHE_H
#define AUDIO_CACHE_H

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include <SDL2pp/SDL2pp.hh>
#include <yaml-cpp/yaml.h>

using namespace SDL2pp;  // NOLINT
using std::map;
using std::string;
using std::vector;

#define AUDIO_PATH "../client/assets/audio/"

class AudioCache {
private:
    static map<string, Chunk> sfxCache;
    static map<string, Music> musicCache;

public:
    AudioCache() = delete;
    ~AudioCache() = delete;

    static Chunk& GetSFXData(const string& filename) {
        auto it = sfxCache.find(filename);
        if (it != sfxCache.end()) {
            return it->second;
        }

        sfxCache.emplace(filename, Chunk(AUDIO_PATH + filename));
        return sfxCache.at(filename);
    }

    static Music& GetMusicData(const string& filename) {
        auto it = musicCache.find(filename);
        if (it != musicCache.end()) {
            return it->second;
        }

        musicCache.emplace(filename, Music(AUDIO_PATH + filename));
        return musicCache.at(filename);
    }

    static void Clear() {
        sfxCache.clear();
        musicCache.clear();
    }
};
map<string, Chunk> AudioCache::sfxCache;
map<string, Music> AudioCache::musicCache;

#endif
