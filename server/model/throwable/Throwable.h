#ifndef THROWABLE_H
#define THROWABLE_H
#include <optional>
#define NOT_THROWED 0
#include "common/RigidBody.h"
#include "data/snapshot.h"
#include "server/model/DynamicObj.h"
#include "server/model/event/ThrowableEventListener.h"


class StaticMap;
class Throwable: public DynamicObject {
    // luce igual que un collectable (pero a este se le sacò el seguro)
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
    virtual ~Throwable() = default;
    virtual TypeCollectable GetTypeCollectable() = 0;

    ThrowableSpawnEventDto GetMovingEventDto();
};


#endif
