#include "ChestplateRenderer.h"

ChestplateRenderer::ChestplateRenderer(Transform& playerT, ArmorData data, int targetFPS):
        Object2D(data.file, playerT),
        playerT(playerT),
        anim(ARMOR_DEFAULT_FRAME, data.frames, targetFPS) {
    transform.SetSize(playerT.GetSize() * 1.05f);
}

void ChestplateRenderer::SetAnimTarget(string animTarget, bool resetIndex) {
    if (!anim.TargetExists(ARMOR_FRAME_PREFIX + animTarget)) {
        anim.SetTarget(ARMOR_DEFAULT_FRAME, resetIndex);
        return;
    }
    anim.SetTarget(ARMOR_FRAME_PREFIX + animTarget, resetIndex);
}

ChestplateRenderer::~ChestplateRenderer() = default;

void ChestplateRenderer::Update(float deltaTime, bool flip) {
    transform.SetSize(playerT.GetSize() * 1.05f);
    transform.SetPos(playerT.GetPos() + Vector2D::Down() * 0.12f);
    SetFlip(flip);
    anim.Update(deltaTime, *this);
}
