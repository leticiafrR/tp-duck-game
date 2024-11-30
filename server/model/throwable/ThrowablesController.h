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
    void Reapdead();

public:
    ThrowablesController();
    void RegisterListener(ThrowableEventListener* listener);
    void Throw(std::shared_ptr<Throwable> obj, const Vector2D& origin, const Vector2D& direction);
    void Update(StaticMap& map, float deltaTime);
};
#endif
