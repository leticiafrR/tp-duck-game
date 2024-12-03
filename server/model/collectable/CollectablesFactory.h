#ifndef COLLECTABLES_FACTORY_H
#define COLLECTABLES_FACTORY_H

#include <memory>
#include <optional>

#include "server/model/projectile/ProjectilesController.h"

class Collectable;
#include "server/config.h"

class CollectablesFactory {
private:
    ProjectilesController& projectilesController;
    const Config& conf;
    TypeItem GetRandomTypeCollectable(int cantAditionalOptions = 0);

public:
    CollectablesFactory(ProjectilesController& projectilesController, const Config& conf);

    std::shared_ptr<Collectable> CreateCollectable(TypeItem type, const Vector2D& position);
    std::shared_ptr<Collectable> CreateRandomCollectable(const Vector2D& position);
    std::optional<std::shared_ptr<Collectable>> MaybeRandomCollectable(const Vector2D& position);
};


#endif
