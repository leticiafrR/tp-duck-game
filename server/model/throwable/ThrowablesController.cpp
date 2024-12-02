#include "ThrowablesController.h"

#include "server/model/Duck.h"

ThrowablesController::ThrowablesController(): unicID(0), l(nullptr) {}
void ThrowablesController::RegisterListener(ThrowableEventListener* listener) { l = listener; }

void ThrowablesController::Throw(std::shared_ptr<Throwable> obj, const Vector2D& origin,
                                 const Vector2D& direction) {
    obj->BeThrown(origin, direction);
    throwables[unicID] = obj;
    unicID++;
}

void ThrowablesController::Update(StaticMap& map, float deltaTime,
                                  std::unordered_map<PlayerID_t, Duck*>& ducks) {
    for (auto& pair: throwables) {
        pair.second->Update(map, deltaTime);
        pair.second->CheckCollisionWithDucks(ducks);
    }
    Reapdead();
}

void ThrowablesController::Reapdead() {
    for (auto it = throwables.begin(); it != throwables.end();) {
        if (it->second->IsDead()) {
            l->Despawning(it->first);
            it = throwables.erase(it);
        } else {
            l->Moving(it->first, it->second->GetMovingEventDto());
            ++it;
        }
    }
}
