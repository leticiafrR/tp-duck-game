#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <functional>

#define TEXTURE_PATH "../assets/sprites/"
#define SHEET_DATA_PATH "../assets/sheet_data/"
#define FONT_PATH "../assets/fonts/"
#define AUDIO_PATH "../assets/audio/"

using Callback = std::function<void()>;
template <typename T>
using Function = std::function<T()>;
template <typename T>
using CallbackParam = std::function<void(T)>;

#endif
