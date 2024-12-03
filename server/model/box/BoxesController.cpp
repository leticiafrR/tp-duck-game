#include "BoxesController.h"

#include "../physicsConstants.h"
#include "server/model/collectable/CollectablesController.h"
#include "server/model/collectable/CollectablesFactory.h"
#include "server/model/projectile/ProjectilesController.h"

BoxesController::BoxesController(const std::unordered_map<BoxID_t, Vector2D>& positionsPerBox,
                                 CollectablesFactory& factory, const Config& conf):
        factory(factory), conf(conf), listener(nullptr) {
    for (auto& pair: positionsPerBox) {
        boxes.emplace(pair.first,
                      Box(Transform(pair.second, Vector2D(conf.getBoxSize(), conf.getBoxSize())),
                          conf.getBoxLife()));
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
            projectiles.RelaseExplotion(boxes[id].GetTransform().GetPos(), conf.getFragmentBox());
        }
    }
}

void BoxesController::Update(CollectablesController& collectables,
                             ProjectilesController& projectiles) {
    for (auto it = boxes.begin(); it != boxes.end();) {
        if (it->second.IsDead()) {
            RelaseContent(it->first, collectables, projectiles);
            listener->DespawnBox(it->first);
            it = boxes.erase(it);
        } else {
            ++it;
        }
    }
}


std::unordered_map<BoxID_t, Box>& BoxesController::GetBoxes() { return boxes; }
