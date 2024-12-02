#include "BulletsController.h"

BulletsController::BulletsController(ResourceManager& resourceManager, AudioManager& audioManager):
        resourceManager(resourceManager), audioManager(audioManager) {}

BulletsController::~BulletsController() = default;

void BulletsController::SpawnBullet(ProjectileEventDto projectilEventData) {

    ProjectileData projectilData = resourceManager.GetProjectilData(projectilEventData.type);

    bullets.emplace_back(projectilData, projectilEventData.origin, projectilEventData.end);
    audioManager.PlaySFX(projectilData.sfxFile);
}
void BulletsController::ReapDead() {
    bullets.remove_if([](BulletRenderer p) { return !p.IsAlive(); });
}

void BulletsController::Draw(float deltaTime, Camera& cam) {
    for (auto& it: bullets) {
        it.Update(deltaTime);
        it.Draw(cam);
    }
}
