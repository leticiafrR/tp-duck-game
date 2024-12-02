#ifndef THROWABLE_H
#define THROWABLE_H
#include <optional>
#include <unordered_map>

#include "common/RigidBody.h"
#include "data/snapshot.h"
#include "server/model/DynamicObj.h"
class Duck;
class StaticMap;
class Throwable: public DynamicObject {
private:
    TypeItem type;
    Vector2D GetForceToBeThrown(const Vector2D& direction);
    void ApplyGravity(const StaticMap& map, float deltaTime) override;
    void HandleCollisionWithMap(const Transform& mapT) override;
    void HandleOutOfBounds(float /* disp*/) override;

protected:
    RigidBody body;
    bool isGrounded;
    bool beenThrowed;

public:
    Throwable(float mass, TypeItem type);
    void BeThrown(const Vector2D& origin, const Vector2D& direction);
    void FollowPosition(const Vector2D& duckPos);
    virtual void Update(const StaticMap& map, float deltaTime);

    ThrowableSpawnEventDto GetMovingEventDto() const;
    virtual void CheckCollisionWithDucks(std::unordered_map<PlayerID_t, Duck*>& players) = 0;
    virtual ~Throwable() = default;
};


#endif
