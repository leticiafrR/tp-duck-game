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
    bool isShooting;  // just touched by the ones who needs key up and key down (not used as the
                      // momment)
    bool isCrouched;
    bool isGrounded;
    MotionHandler motionHandler;
    RigidBody body;
    PlayerEventListener* l;
    Flip myFlip;
    DuckState myState;
    Collectable* itemInHand;
    TypeCollectable typeInHand;

public:
    explicit Duck(const Vector2D& initialPos, ProjectilesController& projectilesController);
    void SayImShooting();  // de juguete: solo para que pueda compilar a los demàs sin que aparezca
                           // que hay una variable sin usar

    void TryMoveLeft();
    void TryMoveRight();
    void StopMoveRight();
    void StopMoveLeft();
    void TryJump();


    void TryUseItem();
    void StopUseItem();


    // void TryCollect();

    void HandleCollisionWithMap(const Transform& mapT) override;
    void HandleOutOfBounds(float displacement) override;
    void HandleDead() override;
    void HandleReceiveDamage(uint8_t damage) override;

    void ApplyGravity(StaticMap& map, float deltaTime) override;

    void RegistListener(PlayerEventListener* listener);
    void UpdateListener(const DuckState& initialState, const Vector2D& initialPos);
    void UpdateState();
    void Update(StaticMap& map, float deltaTime);


    ~Duck() override = default;
    const Flip& GetFlip() const;
    // not copyable
    Duck(const Duck&) = delete;
    Duck& operator=(const Duck&) = delete;
};
#endif
