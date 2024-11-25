#ifndef TEXTURE_CACHE_H
#define TEXTURE_CACHE_H

#include <map>
#include <string>

#include <SDL2pp/SDL2pp.hh>

using SDL2pp::Renderer;
using SDL2pp::Texture;
using std::map;
using std::string;

#define TEXTURE_PATH "../client/assets/sprites/"

class TextureCache {
private:
    Renderer& render;
    map<string, Texture> cache;

public:
    Texture& GetTexture(string filename) {
        auto it = cache.find(filename);
        if (it != cache.end()) {
            return it->second;
        }
        cache.emplace(filename, Texture(render, TEXTURE_PATH + filename));
        // Here we can throw an exception if the texture couldn't be loaded

        return cache.at(filename);
    }

    void Clear() { cache.clear(); }
    void ClearItem(string filename) {
        if (cache.contains(filename))
            cache.erase(filename);
    }

    explicit TextureCache(Renderer& render): render(render) {}

    ~TextureCache() { cache.clear(); }
};

#endif
