#include "CollectablesController.h"

void CollectablesController::ReleasePewPew() {
    if (!unicCollectable) {
        unicCollectable =
                new PewPewLaser(projectilesController,
                                Transform(*weaponSpawnPoints.begin(),
                                          Vector2D(conf.getDuckSize(), conf.getDuckSize())),
                                conf);
    }
}

CollectablesController::CollectablesController(ProjectilesController& projectilesController,
                                               const Config& conf,
                                               const std::vector<Vector2D>& weaponSpawnPoints):
        weaponSpawnPoints(weaponSpawnPoints),
        projectilesController(projectilesController),
        unicCollectable(nullptr),
        conf(conf) {
    std::cout << "was created a pewpewlaser on " << (*weaponSpawnPoints.begin()).ToString() << "\n";
}

void CollectablesController::SayHello() { std::cout << "hola\n"; }


CollectablesController::~CollectablesController() {
    if (unicCollectable) {
        delete unicCollectable;
    }
}


Collectable* CollectablesController::PickCollectable(const Transform& collectorSpace,
                                                     TypeCollectable& collectorType) {
    std::cout << "se intenta pickear un collectable\n";
    if (unicCollectable &&
        Collision::RectCollision(unicCollectable->GetTransform(), collectorSpace)) {
        unicCollectable->BeCollected(collectorType);
        Collectable* collected = unicCollectable;
        unicCollectable = nullptr;
        std::cout << "se recogiò la pewpew\n";
        return collected;
    }
    return nullptr;
}

void CollectablesController::Drop(Collectable* obj, const Vector2D& position) {
    obj->BeDropped(position);
    if (!unicCollectable) {
        unicCollectable = obj;
        std::cout << "[drop controlller] se logra posicionar de vuelta en la pos "
                  << position.ToString() << std::endl;
    }
}

// Collectable* CollectablesController::PickCollectable(const Transform& collectorSpace,
//                                                      TypeCollectable& collectorType) {
//     auto it = std::find_if(collectables.begin(), collectables.end(),
//                            [&collectorSpace](Collectable* obj) {
//                                return Collision::RectCollision(obj->GetTransform(),
//                                collectorSpace);
//                            });

//     if (it != collectables.end()) {
//         (*it)->BeCollected(collectorType);
//         Collectable* collectedObj = *it;
//         collectables.erase(it);
//         // here should call to respawner()
//         return collectedObj;
//     }
//     return nullptr;
// }

/*Hay dos posibles mètodos para agregar un collectable al mapa:Drop o Respawn*/
// void CollectablesController::Drop(Collectable* obj, const Vector2D& position) {
//     obj->BeDropped(position);
//     collectables.push_back(obj);
// }

// CollectablesController::~CollectablesController() {
//     for (Collectable* obj: collectables) {
//         delete obj;
//     }
//     collectables.clear();
// }
