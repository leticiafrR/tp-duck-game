#include "TextureCache.h"

TextureCache::TextureCache(Renderer& render): render(render) {}

TextureCache::~TextureCache() { cache.clear(); }

Texture& TextureCache::GetTexture(string filename) {
    auto it = cache.find(filename);
    if (it != cache.end()) {
        return it->second;
    }
    cache.emplace(filename, Texture(render, TEXTURE_PATH + filename));
    return cache.at(filename);
}

void TextureCache::Clear() { cache.clear(); }

void TextureCache::ClearItem(string filename) {
    if (cache.contains(filename))
        cache.erase(filename);
}
