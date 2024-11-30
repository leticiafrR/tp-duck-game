#include "ThrowablesController.h"


ThrowablesController::ThrowablesController(): unicID(0), l(nullptr) {}

void ThrowablesController::RegisterListener(ThrowableEventListener* listener) { l = listener; }

void ThrowablesController::Throw(std::shared_ptr<Throwable> obj, const Vector2D& origin,
                                 const Vector2D& direction) {
    obj->BeThrown(origin, direction);
    throwables[unicID] = obj;
    unicID++;
    std::cout << "se arrojò el throwable con id: " << (int)unicID;
}

void ThrowablesController::Update(StaticMap& map, float deltaTime) {
    for (auto& pair: throwables) {
        pair.second->Update(map, deltaTime);
        // deberìa ser un throwableMovingEventDto
        if (pair.second->IsDead()) {
            l->Despawning(pair.first);
        } else {
            l->Spawning(pair.first, pair.second->GetMovingEventDto());
        }
    }
    Reapdead();
}

void ThrowablesController::Reapdead() {
    for (auto it = throwables.begin(); it != throwables.end();) {
        if (it->second->IsDead()) {
            it = throwables.erase(it);
        } else {
            ++it;
        }
    }
}
