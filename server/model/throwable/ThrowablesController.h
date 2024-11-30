#ifndef THROWABLE_PROJECTILES_CONTROLLER_H
#define THROWABLE_PROJECTILES_CONTROLLER_H
#include <memory>
#include <unordered_map>

#include "server/model/event/ThrowableEventListener.h"

#include "Throwable.h"
// class Banana;
// class ActiveBananas {
//     private:
//     std::unordered_map<ThrowableID_t,std::shared_ptr<Banana>> activeBananas;
//     public:
//     void NewActiveBanana(ThrowableID_t bananaID,std::shared_ptr<Banana> banana){
//         activeBananas[bananaID] = banana;
//     }
//     void CheckCollisionWithDuck(Duck* duck){
//         for (auto& pair: activeBananas){

//             Collision::RectCollision(pair.second)
//         }
//     }
// }

class ThrowablesController {
private:
    ThrowableID_t unicID;

    std::unordered_map<ThrowableID_t, std::shared_ptr<Throwable>> throwables;
    ThrowableEventListener* l;
    void Reapdead() {
        for (auto it = throwables.begin(); it != throwables.end();) {
            if (it->second->IsDead()) {
                it = throwables.erase(it);
            } else {
                ++it;
            }
        }
    }

public:
    ThrowablesController(): unicID(0), l(nullptr) {}

    void RegisterListener(ThrowableEventListener* listener) { l = listener; }

    void Throw(std::shared_ptr<Throwable> obj, const Vector2D& origin, const Vector2D& direction) {
        obj->BeThrown(origin, direction);
        throwables[unicID] = obj;
        l->Spawning(unicID, obj->GetMovingEventDto());
        unicID++;
        std::cout << "se arrojò el throwable con id: " << (int)unicID;
    }

    void Update(StaticMap& map, float deltaTime) {
        for (auto& pair: throwables) {
            pair.second->Update(map, deltaTime);
            // deberìa ser un throwableMovingEventDto
            l->Spawning(pair.first, pair.second->GetMovingEventDto());
        }
        Reapdead();
    }
};
#endif
