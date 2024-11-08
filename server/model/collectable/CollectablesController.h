#ifndef COLLECTABLES_CONTROLLER_H
#define COLLECTABLES_CONTROLLER_H

#include <algorithm>
#include <vector>

#include "Collectable.h"


class Transform;

class CollectablesController {
private:
    std::vector<Collectable*> collectables;
    /*Spawner spawner; administra spawnplaces, desde que una es*/

public:
    Collectable* PickCollectable(const Transform& collectorSpace,
                                 TypeCollectable& collectorTyperRef);
    void Drop(Collectable* obj, const Vector2D& position);
    /*void Respawn(); faltante*/
    ~CollectablesController();
};


/**********************************  METHODS  ***********************************************/

Collectable* CollectablesController::PickCollectable(const Transform& collectorSpace,
                                                     TypeCollectable& collectorType) {
    auto it = std::find_if(collectables.begin(), collectables.end(),
                           [&collectorSpace](Collectable* obj) {
                               return Collision::RectCollision(obj->GetTransform(), collectorSpace);
                           });

    if (it != collectables.end()) {
        (*it)->BeCollected(collectorType);
        Collectable* collectedObj = *it;
        collectables.erase(it);
        // here should call to respawner()
        return collectedObj;
    }
    return nullptr;
}

/*Hay dos posibles mètodos para agregar un collectable al mapa:Drop o Respawn*/
void CollectablesController::Drop(Collectable* obj, const Vector2D& position) {
    obj->BeDropped(position);
    collectables.push_back(obj);
}

CollectablesController::~CollectablesController() {
    for (Collectable* obj: collectables) {
        delete obj;
    }
    collectables.clear();
}

#endif
