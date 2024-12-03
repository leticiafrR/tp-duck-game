#include "Equipment.h"

Equipment::Equipment(): armor(TypeItem::EMPTY), helmet(TypeItem::EMPTY) {}
bool Equipment::HasArmor() { return (armor != TypeItem::EMPTY); }
bool Equipment::HasHelmet() { return (helmet != TypeItem::EMPTY); }
bool Equipment::TryEquip(TypeItem& item) {

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

bool Equipment::AbsorbDamage() {
    if (HasHelmet()) {
        helmet = TypeItem::EMPTY;
    } else if (HasArmor()) {
        armor = TypeItem::EMPTY;
    } else {
        return false;
    }
    return true;
}
