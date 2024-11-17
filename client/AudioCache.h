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
    static map<string, Chunk> cache;

public:
    AudioCache() = delete;
    ~AudioCache() = delete;

    static Chunk& GetData(const string& filename) {
        auto it = cache.find(filename);
        if (it != cache.end()) {
            return it->second;
        }

        cache.emplace(filename, Chunk(AUDIO_PATH + filename));
        return cache.at(filename);
    }

    static void Clear() { cache.clear(); }
};
map<string, Chunk> AudioCache::cache;

#endif
