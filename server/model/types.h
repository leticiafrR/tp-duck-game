#ifndef TYPES_H
#define TYPES_H
#include <cstdint>

namespace Cooldown {
constexpr float NONE = 0;
constexpr float BASIC = 0.3;  // for every weapon with long shot
constexpr float SHORT = 1;
constexpr float MEDIUM = 2.5;
constexpr float LONG = 7.5;
constexpr float TO_EXPLOTE_GRANADA = 4;

}  // namespace Cooldown

namespace Damage {
constexpr uint8_t MINIMUN = 10;
constexpr uint8_t SHORT = 12;
constexpr uint8_t MEDIUM = 17;
constexpr uint8_t LONG = 20;
//...
}  // namespace Damage

namespace Scope {
constexpr float GRANADA = 20;
constexpr float BANANA = 10;
constexpr float LASER_RIFLE = 30;
constexpr float PISTOLA_COWBOY = 20;
//...
}  // namespace Scope

namespace Ammo {
constexpr uint8_t GRANADA = 1;
constexpr uint16_t BANANA = 1;
constexpr uint16_t LASER_RIFLE = 10;
constexpr uint16_t PISTOLA_COWBOY = 6;
//...
}  // namespace Ammo

namespace Speed {
constexpr int DUCK = 12;
}  // namespace Speed

namespace Size {
constexpr int DUCK = 3;
}  // namespace Size

namespace Mass {
constexpr int DUCK = 15;  // en 7 ticks de 0.4s realiza 1 salto
}  // namespace Mass

namespace Life {
constexpr int DUCK = 100;
}  // namespace Life

namespace DispersionRange {
constexpr float NO_DISPERSION = 0;
constexpr float LONG = 0.4;
constexpr float SHORT = 0.15;
}  // namespace DispersionRange


#endif
