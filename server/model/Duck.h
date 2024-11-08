#ifndef DUCK_H
#define DUCK_H
#include "common/RigidBody.h"
#include "event/PlayerEventListener.h"

#include "DynamicObj.h"
#include "MotionHandler.h"

class Duck: public DynamicObject {
private:
    bool isShooting;
    bool isCrouched;
    bool isGrounded;
    MotionHandler motionHandler;
    RigidBody body;  // could be soported by te collectables
    PlayerEventListener* l;
    Flip myFlip;
    DuckState myState;

public:
    explicit Duck(const Vector2D& initialPos);
    void TryMoveLeft();
    void TryMoveRight();
    void StopMoveRight();
    void StopMoveLeft();
    void TryJump();
    void HandleCollisionWithMap(const Transform& mapT) override;
    void HandleOutOfBounds(float displacement) override;
    void ApplyGravity(StaticMap& map, float deltaTime) override;

    void RegistListener(PlayerEventListener* listener);
    void UpdateListener(const DuckState& initialState, const Vector2D& initialPos);
    void UpdateState();
    void Update(StaticMap& map, float deltaTime);


    ~Duck() override = default;
};
#endif
