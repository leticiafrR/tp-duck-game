#ifndef THROWABLE_PROJECTILES_CONTROLLER_H
#define THROWABLE_PROJECTILES_CONTROLLER_H
#include <memory>
#include <unordered_map>

#include "server/model/event/ThrowableEventListener.h"
// #include "BananaPeels.h"

#include "Throwable.h"

class ThrowablesController {
private:
    ThrowableID_t unicID;
    std::unordered_map<ThrowableID_t, std::shared_ptr<Throwable>> throwables;
    ThrowableEventListener* l;
    // BananaPeels bananaPeels;
    void Reapdead();

public:
    ThrowablesController();
    void RegisterListener(ThrowableEventListener* listener);
    void Throw(std::shared_ptr<Throwable> obj, const Vector2D& origin, const Vector2D& direction);
    void Update(StaticMap& map, float deltaTime);
};
#endif
