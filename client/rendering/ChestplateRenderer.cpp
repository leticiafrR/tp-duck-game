#include "ChestplateRenderer.h"

ChestplateRenderer::ChestplateRenderer(Transform& playerT, int targetFPS):
        Object2D("defense.png", playerT),
        playerT(playerT),
        anim(*this, "defense.yaml", "chest_equiped_idle", targetFPS) {
    transform.SetSize(transform.GetSize() * 1.2f);
}

void ChestplateRenderer::SetAnimTarget(string animTarget, bool resetIndex) {
    if (!anim.TargetExists("chest_equiped_" + animTarget)) {
        anim.SetTarget("chest_equiped_idle", resetIndex);
        return;
    }
    anim.SetTarget("chest_equiped_" + animTarget, resetIndex);
}

ChestplateRenderer::~ChestplateRenderer() = default;

void ChestplateRenderer::Update(float deltaTime) {
    transform.SetPos(playerT.GetPos() + Vector2D::Down() * 0.2f);
    anim.Update(deltaTime);
}
