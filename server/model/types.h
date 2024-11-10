#ifndef TYPES_H
#define TYPES_H
#include <cstdint>

enum class TypeCollectable {
    Empty,
    Helmet,
    Armor,
    Granada,
    Banana,
    Laser,
    Ak47,
    PistolaDuelo,
    PistolaCowboy,
    Magnum,
    Escopeta,
    Sniper
};
// enum class TypeHelmet { NoHelmet, KnightsHelmet, Helmet};
// enum class TypeArmor { NoArmor,Chestplate};

namespace Time {
constexpr uint8_t COOLDOWN_SHORT = 3;
constexpr uint8_t COOLDOWN_MEDIUM = 6;
constexpr uint8_t COOLDOWN_LONG = 9;
constexpr uint8_t TO_EXPLOTE_GRANADA = 4;
}  // namespace Time

namespace Damage {
constexpr uint8_t MINIMUN = 1;
constexpr uint8_t SHORT = 2;
constexpr uint8_t MEDIUM = 6;
constexpr uint8_t LONG = 8;
//...
}  // namespace Damage

namespace Scope {
constexpr uint8_t GRANADA = 20;
constexpr uint8_t BANANA = 10;
constexpr uint8_t LASER = 30;
//...
}  // namespace Scope

namespace Ammo {
constexpr uint8_t GRANADA = 1;
constexpr uint16_t BANANA = 1;
constexpr uint16_t LASER = 10;
//...
}  // namespace Ammo

namespace Speed {
constexpr int DUCK = 10;  // to make the duck moves fastly per tick, add here
}  // namespace Speed

namespace Size {
constexpr int DUCK = 5;
constexpr int BULLET = 2;
}  // namespace Size

namespace Mass {
constexpr int DUCK = 8;  // en 7 ticks de 0.4s realiza 1 salto
}  // namespace Mass


/*si un pato se colisiona por arriba asumo que solo puede ser saltando*/

#endif
