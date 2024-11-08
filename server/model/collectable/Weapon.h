#ifndef WEAPON_H
#define WEAPON_H
#include "../Duck.h"

#include "Collectable.h"
#define RATE 10  //<-CUESTIONABLE

class ProjectilesController;

class Weapon: public Collectable {
protected:
    ProjectilesController& projectilesController;
    const uint8_t scope;
    uint16_t ammo;

public:
    Weapon(ProjectilesController& projectilesController, const Transform& initialSpace,
           uint8_t scope, uint16_t ammo):
            Collectable(initialSpace),
            projectilesController(projectilesController),
            scope(scope),
            ammo(ammo) {}

    virtual void BeCollected(TypeCollectable& collectorTypeRef) override = 0;
    virtual void Use(Duck* shooter) override = 0;
    virtual ~Weapon();

    /*de esta derivan:
        -> Guns
        -> Banana
        -> Granada*/
};


/******************************PRODUCTORES DE
 * PROYECTILES:BULLETS*********************************************+*/
class Gun: public Weapon {
protected:
    const uint8_t cooldown;
    int cooldownTimer;

public:
    Gun(ProjectilesController& projectilesController, const Transform& initialSpace, uint8_t scope,
        uint16_t ammo, uint8_t cooldown):
            Weapon(projectilesController, initialSpace, scope, ammo),
            cooldown(cooldown),
            cooldownTimer(0) {}

    virtual void BeCollected(TypeCollectable& collectorTypeRef) override = 0;
    virtual void Use(Duck* shooter) override { shooter->Shoot(); }
    virtual void Update() { cooldownTimer += RATE; }

    /* de esta derivan (todas las que tienen disparos prolongados):
        -> LaserRifle
        -> PistolaDuelos
        -> etc
    */
};

class LaserRifle: public Gun {
public:
    explicit LaserRifle(ProjectilesController& projectilesController,
                        const Transform& initialSpace):
            Gun(projectilesController, initialSpace, Scope::LASER, Ammo::LASER,
                Time::COOLDOWN_SHORT) {}

    void BeCollected(TypeCollectable& collectorTypeRef) override {
        collectorTypeRef = TypeCollectable::Laser;
    }

    void Use(Duck* shooter) override {
        Gun::Use(shooter);
        // shooter->ApplyRetrocces();
        /*logic to shoot, aqui es donde se usa el ProjectilesController*/
    }
};

/*****************************PRODUCTORES DE PROYECTILES:NO
 * BULLETS********************************************/

class Banana: public Weapon {
public:
    explicit Banana(ProjectilesController& projectilesController, const Transform& initialSpace):
            Weapon(projectilesController, initialSpace, Scope::BANANA, Ammo::BANANA) {}

    void BeCollected(TypeCollectable& collectorTypeRef) override {
        collectorTypeRef = TypeCollectable::Banana;
    }
};

class Granada: public Weapon {
private:
    const uint8_t timeToExplote;
    uint8_t timer;

public:
    explicit Granada(ProjectilesController& projectilesController, const Transform& initialSpace):
            Weapon(projectilesController, initialSpace, Scope::GRANADA, Ammo::GRANADA),
            timeToExplote(Time::TO_EXPLOTE_GRANADA),
            timer(0) {}

    void BeCollected(TypeCollectable& collectorTypeRef) override {
        collectorTypeRef = TypeCollectable::Granada;
    }
};


#endif
