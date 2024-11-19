#ifndef DUCK_H
#define DUCK_H
#include "collectable/Collectable.h"
#include "common/RigidBody.h"
#include "event/PlayerEventListener.h"

#include "DynamicObj.h"
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

    MotionHandler motionHandler;
    RigidBody body;
    PlayerEventListener* l;
    Flip myFlip;
    DuckState myState;
    // DamageState damageState;
    Collectable* itemInHand;
    TypeCollectable typeInHand;

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

    void HandleCollisionWithMap(const Transform& mapT) override;
    void HandleOutOfBounds(float displacement) override;
    void HandleDead() override;
    void HandleReceiveDamage(uint8_t damage) override;

    void ApplyGravity(StaticMap& map, float deltaTime) override;

    void RegistListener(PlayerEventListener* listener);
    void UpdateListener(const DuckState& initialState, const Vector2D& initialPos);
    DuckState GetLowerPriorityState();
    void UpdateState();
    void Update(StaticMap& map, float deltaTime);
    const Flip& GetFlip() const;

    ~Duck() override = default;
    Duck(const Duck&) = delete;
    Duck& operator=(const Duck&) = delete;
};
#endif
