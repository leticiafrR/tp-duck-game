#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <functional>

#define TEXTURE_PATH "/var/duckGame_g6/assets/sprites/"
#define SHEET_DATA_PATH "/var/duckGame_g6/assets/sheet_data/"
#define FONT_PATH "/var/duckGame_g6/assets/fonts/"
#define AUDIO_PATH "/var/duckGame_g6/assets/audio/"

using Callback = std::function<void()>;
template <typename T>
using Function = std::function<T()>;
template <typename T>
using CallbackParam = std::function<void(T)>;

#endif
