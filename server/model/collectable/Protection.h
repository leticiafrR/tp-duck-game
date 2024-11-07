#ifndef PROTECTION_H
#define PROTECTION_H
#include "../types.h"

#include "Collectable.h"
//#include "../Duck.h" //incluye equipment que inlcuye tipos
#include <iostream>

class Armor: public Collectable {
public:
    explicit Armor(Transform initialSpace): Collectable(initialSpace) {}
    void BeCollected(TypeCollectable& collectorTypeRef) override {
        collectorTypeRef = TypeCollectable::Armor;
    }
    // void Use(Duck* user) override { user->EquipProtection();}
    void Use() override { std::cout << "armadura siendo usada\n"; }
    void Saludad() { std::cout << "soy armadura\n"; }
};

class Helmet: public Collectable {
public:
    explicit Helmet(Transform initialSpace): Collectable(initialSpace) {}
    void BeCollected(TypeCollectable& collectorTypeRef) override {
        collectorTypeRef = TypeCollectable::Helmet;
    }

    // void Use(Duck* user) override { user->EquipProtection();}
    void Use() override { std::cout << "helmet siendo usada\n"; }
};

#endif
