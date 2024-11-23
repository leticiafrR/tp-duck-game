#ifndef DUCK_H
#define DUCK_H
#include "collectable/Collectable.h"
#include "common/RigidBody.h"
#include "event/PlayerEventListener.h"
#include "server/config.h"

#include "DynamicObj.h"
#include "Equipment.h"
#include "MotionHandler.h"
class ProjectilesController;

class Duck: public DynamicObject {
private:
    // cppcheck-suppress unusedStructMember

    PlayerID_t id;
    // cppcheck-suppress unusedStructMember
    // cppcheck-suppress unusedStructMember
    bool isShooting;  // just touched by the ones who needs key up and key down (not used as the
                      // cppcheck-suppress unusedStructMember            // momment)
    bool isLookingUp;
    // cppcheck-suppress unusedStructMember
    bool isCrouched;
    // cppcheck-suppress unusedStructMember
    bool isGrounded;
    // cppcheck-suppress unusedStructMember
    bool isWounded;
    // cppcheck-suppress unusedStructMember
    MotionHandler motionHandler;
    // cppcheck-suppress unusedStructMember
    RigidBody body;
    // cppcheck-suppress unusedStructMember
    PlayerEventListener* l;
    // cppcheck-suppress unusedStructMember
    Flip myFlip;
    // cppcheck-suppress unusedStructMember
    DuckState myState;
    // cppcheck-suppress unusedStructMember
    Collectable* itemOnHand;
    // cppcheck-suppress unusedStructMember
    TypeCollectable typeOnHand;
    // cppcheck-suppress unusedStructMember
    Equipment protectiveEquipment;

    void UpdateListener(const DuckState& initialState, const Vector2D& initialPos);
    DuckState GetLowerPriorityState();
    void UpdateState();
    void UpdateWeapon(float deltaTime);
    bool HasWeaponOnHand();
    void TriggerEvent();

public:
    explicit Duck(const Vector2D& initialPos, PlayerID_t id,
                  ProjectilesController& projectilesController, const Config& conf);
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
