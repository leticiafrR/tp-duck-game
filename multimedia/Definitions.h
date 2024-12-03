#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <functional>

#define TEXTURE_PATH "/var/duckGame_g6/assets/sprites/"
#define RESOURCE_DATA_PATH "/etc/duckGame_g6/rendering/"
#define FONT_PATH "/var/duckGame_g6/assets/fonts/"
#define AUDIO_PATH "/var/duckGame_g6/assets/audio/"

using Callback = std::function<void()>;
template <typename T>
using Function = std::function<T()>;
template <typename T>
using CallbackParam = std::function<void(T)>;

#define BUTTON_FILE "button_1.png"
#define BACK_BUTTON_FILE "back_icon.png"
#define BUTTON_SFX_FILE "buttonSFX.mp3"

#endif
