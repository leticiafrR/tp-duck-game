#ifndef AUDIO_CACHE_H
#define AUDIO_CACHE_H

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include <SDL2pp/SDL2pp.hh>
#include <yaml-cpp/yaml.h>

#include "multimedia/Definitions.h"

using namespace SDL2pp;  // NOLINT
using std::map;
using std::string;
using std::vector;

const int MAX_CHANELS = 20;

class AudioCache {
private:
    Mixer audioMixer;
    map<string, Chunk> sfxMapCache;
    map<string, Music> musicMapCache;

public:
    AudioCache();

    Chunk& GetAudioSFXData(const string& filename);
    Music& GetAudioMusicData(const string& filename);

    Mixer& GetMixer();

    static void Clear();
};

#endif
