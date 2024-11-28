#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "data/snapshot.h"
class Equipment {
private:
    TypeCollectable armor;
    TypeCollectable helmet;

public:
    Equipment(): armor(TypeCollectable::EMPTY), helmet(TypeCollectable::EMPTY) {}
    bool HasArmor() { return (armor != TypeCollectable::EMPTY); }
    bool HasHelmet() { return (helmet != TypeCollectable::EMPTY); }
    bool TryEquip(TypeCollectable& item) {

        if (item == TypeCollectable::ARMOR && !HasArmor()) {
            armor = item;
            item = TypeCollectable::EMPTY;
            return true;
        }
        if (item == TypeCollectable::HELMET && !HasHelmet()) {
            helmet = item;
            item = TypeCollectable::EMPTY;
            return true;
        }
        return false;
    }
    bool AbsorbDamage() {
        if (HasHelmet()) {
            helmet = TypeCollectable::EMPTY;
        } else if (HasArmor()) {
            armor = TypeCollectable::EMPTY;
        } else {
            return true;
        }
        return false;
    }
};
#endif
