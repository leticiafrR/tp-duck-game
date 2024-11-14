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
    // cppcheck-suppress unusedStructMember
    [[clang::supress_unused]] bool isShooting;
    // cppcheck-suppress unusedStructMember
    [[clang::supress_unused]] bool isCrouched;
    // cppcheck-suppress unusedStructMember
    [[clang::supress_unused]] bool isGrounded;
    // cppcheck-suppress unusedStructMember
    [[clang::supress_unused]] MotionHandler motionHandler;
    // cppcheck-suppress unusedStructMember
    [[clang::supress_unused]] RigidBody body;  // could be soported by te collectables
    // cppcheck-suppress unusedStructMember
    [[clang::supress_unused]] PlayerEventListener* l;
    // cppcheck-suppress unusedStructMember
    [[clang::supress_unused]] Flip myFlip;
    // cppcheck-suppress unusedStructMember
    [[clang::supress_unused]] DuckState myState;
    // TypeInHand type;
    // cppcheck-suppress unusedStructMember
    [[clang::supress_unused]] Collectable* itemInHand;

public:
    explicit Duck(const Vector2D& initialPos, ProjectilesController& projectilesController);
    void SayHello();  // de juguete: solo para que pueda compilar a los demàs sin que aparezca que
                      // hay una variable sin usar

    void TryMoveLeft();
    void TryMoveRight();
    void StopMoveRight();
    void StopMoveLeft();
    void TryJump();
    void TryUseItem();
    // pendientes:
    void StopUseItem();

    // void TryCollect();

    void HandleCollisionWithBullet(uint8_t damage);

    void HandleCollisionWithMap(const Transform& mapT) override;
    void HandleOutOfBounds(float displacement) override;
    void ApplyGravity(StaticMap& map, float deltaTime) override;

    void RegistListener(PlayerEventListener* listener);
    void UpdateListener(const DuckState& initialState, const Vector2D& initialPos);
    void UpdateState();
    void Update(StaticMap& map, float deltaTime);
    void ApplyRetroces();

    ~Duck() override = default;
    // not copyable
    Duck(const Duck&) = delete;
    Duck& operator=(const Duck&) = delete;
};
#endif
