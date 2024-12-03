#include "BoxesController.h"

#include "../physicsConstants.h"
#include "server/config.h"
#include "server/model/collectable/CollectablesController.h"
#include "server/model/collectable/CollectablesFactory.h"
#include "server/model/projectile/ProjectilesController.h"
#define CANT_FRAGMENTS_BOX_EXPLOTION 10

BoxesController::BoxesController(const std::unordered_map<BoxID_t, Vector2D>& positionsPerBox,
                                 CollectablesFactory& factory):
        factory(factory), listener(nullptr) {
    for (auto& pair: positionsPerBox) {
        boxes.emplace(pair.first, Box(pair.second));
    }
}

void BoxesController::RegisterListener(BoxEventListener* l) { listener = l; }


void BoxesController::RelaseContent(BoxID_t id, CollectablesController& collectables,
                                    ProjectilesController& projectiles) {
    std::optional<std::shared_ptr<Collectable>> maybeContent =
            boxes.find(id)->second.GetContent(factory);
    if (maybeContent.has_value()) {
        if (maybeContent.value() != nullptr) {
            collectables.AddCollectable(maybeContent.value());
        } else {
            projectiles.RelaseExplotion(boxes[id].GetTransform().GetPos(),
                                        CANT_FRAGMENTS_BOX_EXPLOTION);
        }
    }
}

void BoxesController::Update(CollectablesController& collectables,
                             ProjectilesController& projectiles) {
    for (auto it = boxes.begin(); it != boxes.end();) {
        if (it->second.IsDead()) {
            std::cout << "una caja habia sido destruida :0 \n";
            RelaseContent(it->first, collectables, projectiles);
            listener->DespawnBox(it->first);
            it = boxes.erase(it);
        } else {
            ++it;
        }
    }
}


std::unordered_map<BoxID_t, Box>& BoxesController::GetBoxes() { return boxes; }
