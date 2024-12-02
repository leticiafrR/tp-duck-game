#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "data/snapshot.h"
class Equipment {
private:
    TypeItem armor;
    TypeItem helmet;

public:
    Equipment(): armor(TypeItem::EMPTY), helmet(TypeItem::EMPTY) {}
    bool HasArmor() { return (armor != TypeItem::EMPTY); }
    bool HasHelmet() { return (helmet != TypeItem::EMPTY); }
    bool TryEquip(TypeItem& item) {

        if (item == TypeItem::ARMOR && !HasArmor()) {
            armor = item;
            item = TypeItem::EMPTY;
            return true;
        }
        if (item == TypeItem::HELMET && !HasHelmet()) {
            helmet = item;
            item = TypeItem::EMPTY;
            return true;
        }
        return false;
    }
    bool AbsorbDamage() {
        if (HasHelmet()) {
            helmet = TypeItem::EMPTY;
        } else if (HasArmor()) {
            armor = TypeItem::EMPTY;
        } else {
            return false;
        }
        return true;
    }
};
#endif
