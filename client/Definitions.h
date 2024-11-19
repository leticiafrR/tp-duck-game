#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <functional>

using Callback = std::function<void()>;

template <typename T>
using Function = std::function<T()>;
template <typename T>
using CallbackParam = std::function<void(T)>;

#endif
