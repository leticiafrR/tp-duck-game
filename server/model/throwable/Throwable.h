#ifndef THROWABLE_H
#define THROWABLE_H
#include <optional>
#define NOT_THROWED 0
#include <unordered_map>

#include "common/RigidBody.h"
#include "data/snapshot.h"
#include "server/model/DynamicObj.h"
#include "server/model/event/ThrowableEventListener.h"
class Duck;
class StaticMap;
class Throwable: public DynamicObject {
protected:
    RigidBody body;
    bool isGrounded;
    bool beenThrown;
    ThrowableEventListener* listener;
    ThrowableID_t throwingID;

    Vector2D GetForceToBeThrown(const Vector2D& direction);

public:
    explicit Throwable(float mass);
    void BeThrown(const Vector2D& origin, const Vector2D& direction, ThrowableEventListener* l,
                  ThrowableID_t throwingID);
    void FollowPosition(const Vector2D& duckPos);
    void ApplyGravity(const StaticMap& map, float deltaTime) override;
    void HandleCollisionWithMap(const Transform& mapT) override;
    void HandleOutOfBounds(float /* disp*/) override;
    virtual void Update(const StaticMap& map, float deltaTime);
    virtual void CheckCollisionWithDucks(std::unordered_map<PlayerID_t, Duck*>& players) = 0;
    virtual ~Throwable() = default;
    virtual TypeCollectable GetTypeCollectable() = 0;

    ThrowableSpawnEventDto GetMovingEventDto();
};


#endif
