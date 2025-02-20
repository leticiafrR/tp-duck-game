#ifndef FONT_CACHE_H
#define FONT_CACHE_H

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

class FontCache {
private:
    map<string, Font> mapCache;

public:
    Font& GetFontData(const string& filename, int fontSize);

    void Clear();
};


#endif
