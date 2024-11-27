#ifndef TEXTURE_CACHE_H
#define TEXTURE_CACHE_H

#include <map>
#include <string>

#include <SDL2pp/SDL2pp.hh>

#include "multimedia/Definitions.h"

using SDL2pp::Renderer;
using SDL2pp::Texture;
using std::map;
using std::string;

class TextureCache {
private:
    Renderer& render;
    map<string, Texture> cache;

public:
    explicit TextureCache(Renderer& render);

    ~TextureCache();

    Texture& GetTexture(string filename);

    void Clear();

    void ClearItem(string filename);
};

#endif
