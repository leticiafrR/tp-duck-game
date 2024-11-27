#ifndef COLLECTABLES_CONTROLLER_H
#define COLLECTABLES_CONTROLLER_H

#include <algorithm>
#include <unordered_map>
#include <vector>

#include "server/config.h"
#include "server/model/event/CollectableEventListener.h"
#include "server/model/projectile/ProjectilesController.h"

#include "Collectable.h"
class Transform;

class CollectablesController {
private:
    CollectableID_t unicID;
    std::vector<Vector2D> weaponSpawnPoints;
    std::unordered_map<CollectableID_t, Collectable*> collectables;

    const Config& conf;
    ProjectilesController& projectilesController;

    CollectableEventListener* listener;

    void SpawnCollectable(Collectable* obj);

public:
    explicit CollectablesController(ProjectilesController& projectilesController,
                                    const Config& conf,
                                    const std::vector<Vector2D>& weaponSpawnPoints);
    void SpawnInitialWeapons();
    void RegisterListener(CollectableEventListener* collectableListener);
    Collectable* PickCollectable(const Transform& collectorSpace,
                                 TypeCollectable& collectorTyperRef);
    void Drop(Collectable* obj, const Vector2D& position);
    // /*void Respawn(); faltante*/
    ~CollectablesController();
};


#endif
