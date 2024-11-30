#ifndef THROWABLE_H
#define THROWABLE_H
#include <optional>

#include "common/RigidBody.h"
#include "data/snapshot.h"
#include "server/model/DynamicObj.h"


class StaticMap;
class Throwable: public DynamicObject {
    // luce igual que un collectable (pero a este se le sacò el seguro)
protected:
    RigidBody body;
    bool isGrounded;
    bool beenThrown;

    Vector2D GetForceToBeThrown(const Vector2D& direction);

public:
    explicit Throwable(float mass);
    void BeThrown(const Vector2D& origin, const Vector2D& direction);

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
