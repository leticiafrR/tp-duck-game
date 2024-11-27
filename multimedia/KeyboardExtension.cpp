#include "KeyboardExtension.h"

std::unordered_set<SDL_Keycode> SDLExtension::AlphaNumericKeys = {
        SDLK_q, SDLK_w, SDLK_e, SDLK_r, SDLK_t, SDLK_y, SDLK_u, SDLK_i, SDLK_o,
        SDLK_p, SDLK_a, SDLK_s, SDLK_d, SDLK_f, SDLK_g, SDLK_h, SDLK_j, SDLK_k,
        SDLK_l, SDLK_z, SDLK_x, SDLK_c, SDLK_v, SDLK_b, SDLK_n, SDLK_m, SDLK_0,
        SDLK_1, SDLK_2, SDLK_3, SDLK_4, SDLK_5, SDLK_6, SDLK_7, SDLK_8, SDLK_9};

std::unordered_set<SDL_Keycode> SDLExtension::SpecialKeys = {
        SDLK_LSHIFT,    SDLK_RSHIFT,   SDLK_LCTRL,     SDLK_RCTRL,     SDLK_LALT,
        SDLK_RALT,      SDLK_ESCAPE,   SDLK_F1,        SDLK_F2,        SDLK_F3,
        SDLK_F4,        SDLK_F5,       SDLK_F6,        SDLK_F7,        SDLK_F8,
        SDLK_F9,        SDLK_F10,      SDLK_F11,       SDLK_F12,       SDLK_TAB,
        SDLK_BACKSPACE, SDLK_CAPSLOCK, SDLK_KP_0,      SDLK_KP_1,      SDLK_KP_2,
        SDLK_KP_3,      SDLK_KP_4,     SDLK_KP_5,      SDLK_KP_6,      SDLK_KP_7,
        SDLK_KP_8,      SDLK_KP_9,     SDLK_KP_PLUS,   SDLK_KP_MINUS,  SDLK_KP_MULTIPLY,
        SDLK_KP_DIVIDE, SDLK_KP_ENTER, SDLK_KP_PERIOD, SDLK_KP_EQUALS, SDLK_NUMLOCKCLEAR};

bool SDLExtension::IsSpecialKey(SDL_Keycode key) {
    return SpecialKeys.find(key) != SpecialKeys.end();
}
bool SDLExtension::IsAlphaNumeric(SDL_Keycode key) {
    return AlphaNumericKeys.find(key) != AlphaNumericKeys.end();
}
