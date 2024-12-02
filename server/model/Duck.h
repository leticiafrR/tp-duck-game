#ifndef DUCK_H
#define DUCK_H
#include <memory>

#include "collectable/Collectable.h"
#include "common/RigidBody.h"
#include "event/PlayerEventListener.h"
#include "server/config.h"
#include "throwable/Throwable.h"

#include "DynamicObj.h"
#include "Equipment.h"
#include "MotionHandler.h"
class ProjectilesController;
class CollectablesController;
class ThrowablesController;

class Duck: public DynamicObject {
private:
    PlayerID_t id;
    const int speedX;
    int life;

    bool isShooting;
    bool isLookingUp;
    bool isCrouched;
    bool isGrounded;
    bool isWounded;
    bool isFlapping;
    const float cooldownFlapping;
    float flappingTimer;

    MotionHandler motionHandler;
    RigidBody body;
    PlayerEventListener* l;
    Flip myFlip;
    DuckState myState;
    std::shared_ptr<Collectable> itemOnHand;
    std::shared_ptr<Throwable> throwableOnHand;
    TypeItem typeOnHand;
    Equipment equipment;
    void UpdateFlapping(float deltaTime);
    void UpdateListener(const DuckState& initialState, const Vector2D& initialPos);
    DuckState GetLowerPriorityState();
    void UpdateState();
    void UpdateHand(const StaticMap& map, float deltaTime);
    void TriggerEvent(bool cuack = false);
    bool TryDropCollectable(CollectablesController& collectables);
    bool TryThrow(ThrowablesController& throwables);
    bool TryUpdateThrowable(const StaticMap& map, float deltaTime);
    void TryUpdateCollectable(float deltaTime);
    void LoseThrowableOnHand();

    void ApplyGravity(const StaticMap& map, float deltaTime) override;
    void HandleCollisionWithMap(const Transform& mapT) override;
    void HandleOutOfBounds(float displacement) override;
    void HandleDead();

public:
    explicit Duck(const Vector2D& initialPos, PlayerID_t id, const Config& conf);
    void TryMoveLeft();
    void TryMoveRight();
    void StopMoveRight();
    void StopMoveLeft();
    void TryJump();
    void TryUseItem();
    void StopUseItem();
    void StartShooting();
    void StopShooting();
    void LookUp();
    void StopLookUp();
    void Crouch();
    void StopCrouch();

    void Cuack();
    void Slide(Vector2D intensity) { body.ApplyForce(intensity); }
    void HandleReceiveDamage(uint8_t damage);

    void TryEquip();

    void TryCollect(CollectablesController& c);
    void TryDrop(CollectablesController& collectables, ThrowablesController& throwables);

    void PrepareToThrow(std::shared_ptr<Throwable> throwable, TypeItem type);
    void ApplyRecoil(float intensity);

    void RegistListener(PlayerEventListener* listener);
    void Update(const StaticMap& map, float deltaTime);
    const Flip& GetFlip() const;
    Vector2D GetLookVector(bool justLaterals = false);
    bool IsShooting() const;

    Duck(const Duck&) = delete;
    Duck& operator=(const Duck&) = delete;
};
#endif
