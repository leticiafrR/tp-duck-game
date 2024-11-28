#include "HelmetRenderer.h"

HelmetRenderer::HelmetRenderer(Transform& playerT):
        Object2D("defense.png", Transform()), follow(transform, playerT) {}

void HelmetRenderer::Update() { follow.Follow(); }

HelmetRenderer::~HelmetRenderer() = default;
