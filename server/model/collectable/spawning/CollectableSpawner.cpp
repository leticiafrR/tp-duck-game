#include "CollectableSpawner.h"

#include "Collectables.h"
#define COLLECTABLE_SIZE 2
CollectableSpawner::CollectableSpawner(const Vector2D& position,
                                       CollectablesFactory& collectablesFactory):
        timeToRespawn(3),
        timer(std::make_shared<float>(0)),
        position(position),
        factory(collectablesFactory) {}

void CollectableSpawner::Update(float deltaTime, Collectables& collectables) {
    if ((*timer) < timeToRespawn && (*timer) + deltaTime >= timeToRespawn) {
        collectables.SpawnCollectable(factory.CreateRandomCollectable(position), timer);
    }
    (*timer) += deltaTime;
}
