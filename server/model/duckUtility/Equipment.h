#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "data/snapshot.h"
class Equipment {
private:
    TypeItem armor;
    TypeItem helmet;

public:
    Equipment();
    bool HasArmor();
    bool HasHelmet();
    bool TryEquip(TypeItem& item);
    bool AbsorbDamage();
};
#endif
