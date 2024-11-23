#ifndef DUCK_H
#define DUCK_H
#include "collectable/Collectable.h"
#include "common/RigidBody.h"
#include "event/PlayerEventListener.h"

#include "DynamicObj.h"
#include "Equipment.h"
#include "MotionHandler.h"
class ProjectilesController;

class Duck: public DynamicObject {
private:
    PlayerID_t id;
    bool isShooting;  // just touched by the ones who needs key up and key down (not used as the
                      // momment)
    bool isCrouched;
    bool isGrounded;
    bool isWounded;
    bool isLookingUp;

    MotionHandler motionHandler;
    RigidBody body;
    PlayerEventListener* l;
    Flip myFlip;
    DuckState myState;
    Collectable* itemOnHand;
    TypeCollectable typeOnHand;
    Equipment protectiveEquipment;

    void UpdateListener(const DuckState& initialState, const Vector2D& initialPos);
    DuckState GetLowerPriorityState();
    void UpdateState();
    void UpdateWeapon(float deltaTime);
    bool HasWeaponOnHand();
    void TriggerEvent();

public:
    explicit Duck(const Vector2D& initialPos, PlayerID_t id,
                  ProjectilesController& projectilesController);
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

    void HandleCollisionWithMap(const Transform& mapT) override;
    void HandleOutOfBounds(float displacement) override;
    void HandleDead() override;
    void HandleReceiveDamage(uint8_t damage) override;

    void ApplyGravity(StaticMap& map, float deltaTime) override;

    void RegistListener(PlayerEventListener* listener);
    void Update(StaticMap& map, float deltaTime);
    const Flip& GetFlip() const;
    Vector2D GetLookVector();
    bool IsShooting() const;

    ~Duck() override = default;
    Duck(const Duck&) = delete;
    Duck& operator=(const Duck&) = delete;
};
#endif
