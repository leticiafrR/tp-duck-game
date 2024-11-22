#ifndef TYPES_H
#define TYPES_H
#include <cstdint>

enum class TypeCollectable {
    EMPTY,
    PISTOLA_COWBOY,
    LASER_RIFLE,
    Helmet,
    Armor,
    Granada,
    Banana,
    Ak47,
    PistolaDuelo,
    Magnum,
    Escopeta,
    Sniper
};

namespace Cooldown {
constexpr uint8_t NONE = 0;
constexpr uint8_t SHORT = 3;
constexpr uint8_t MEDIUM = 6;
constexpr uint8_t LONG = 9;
constexpr uint8_t TO_EXPLOTE_GRANADA = 4;

}  // namespace Cooldown

namespace Damage {
constexpr uint8_t MINIMUN = 10;
constexpr uint8_t SHORT = 12;
constexpr uint8_t MEDIUM = 17;
constexpr uint8_t LONG = 2;
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
constexpr int DUCK = 12;  // to make the duck moves fastly per tick, add here
}  // namespace Speed

namespace Size {
constexpr int DUCK = 3;
// constexpr int BULLET = 2;
}  // namespace Size

namespace Mass {
constexpr int DUCK = 15;  // en 7 ticks de 0.4s realiza 1 salto
}  // namespace Mass

namespace Life {
constexpr int DUCK = 100;
}  // namespace Life


#endif
