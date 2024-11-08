#ifndef EQUIPMENT_H
#define EQUIPMENT_H
#include "types.h"
class Equipment {
private:
    TypeCollectable armor;
    TypeCollectable helmet;

public:
    Equipment(): armor(TypeCollectable::Empty), helmet(TypeCollectable::Empty) {}
    bool TryEquip(TypeCollectable& item) {

        if (item == TypeCollectable::Armor && !HasArmor()) {
            armor = item;
            item = TypeCollectable::Empty;
            return true;
        }
        if (item == TypeCollectable::Helmet && !HasHelmet()) {
            helmet = item;
            item = TypeCollectable::Empty;
            return true;
        }
        return false;
    }
    bool HasArmor() { return (armor != TypeCollectable::Empty); }
    bool HasHelmet() { return (helmet != TypeCollectable::Empty); }
};
#endif
