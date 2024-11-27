#ifndef KEYBOARD_EXTENSION_H
#define KEYBOARD_EXTENSION_H

#include <unordered_set>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>
class SDLExtension {
private:
    static std::unordered_set<SDL_Keycode> SpecialKeys;
    static std::unordered_set<SDL_Keycode> AlphaNumericKeys;

public:
    static bool IsSpecialKey(SDL_Keycode key);
    static bool IsAlphaNumeric(SDL_Keycode key);
};

#endif
