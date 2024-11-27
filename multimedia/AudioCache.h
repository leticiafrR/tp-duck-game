#ifndef AUDIO_CACHE_H
#define AUDIO_CACHE_H

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include <SDL2pp/SDL2pp.hh>
#include <yaml-cpp/yaml.h>

#include "Definitions.h"

using namespace SDL2pp;  // NOLINT
using std::map;
using std::string;
using std::vector;

class AudioCache {
private:
    static map<string, Chunk> sfxCache;
    static map<string, Music> musicCache;

public:
    AudioCache() = delete;
    ~AudioCache() = delete;

    static Chunk& GetSFXData(const string& filename);
    static Music& GetMusicData(const string& filename);

    static void Clear();
};

#endif
