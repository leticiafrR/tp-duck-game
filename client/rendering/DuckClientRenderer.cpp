#include "DuckClientRenderer.h"

DuckClientRenderer::DuckClientRenderer(Vector2D size, Color skinColor,
                                       ResourceManager& resourceManager,
                                       CameraController& camController):
        duckData(resourceManager.GetDuckData()),
        camController(camController),
        anim("idle", duckData.frames, 22),
        handItem(this->transform),
        armor(this->transform, resourceManager.GetArmorData(), 22),
        helmet(this->transform, resourceManager.GetCollectableData(TypeCollectable::HELMET)) {

    this->skinColor = skinColor;
    SetFileName(duckData.file);
    transform.SetSize(size * 1.4f);  // Size rendering offset
    SetColor(skinColor);
    camController.AddTransform(&transform);
}

DuckClientRenderer::~DuckClientRenderer() = default;

Color DuckClientRenderer::GetSkinColor() const { return skinColor; }
std::string DuckClientRenderer::GetNickname() const { return nickname; }

void DuckClientRenderer::Update(float deltaTime) {
    tLerp += deltaTime * 13;

    Vector2D pos = Vector2D::Lerp(fromPos, target.motion, tLerp);
    transform.SetPos(pos);

    if (damaged) {
        SetTargetAnimation("damaged");
        damagedTimer.Update(deltaTime);
    }

    if (cuack) {
        cuackTimer.Update(deltaTime);
    }

    anim.Update(deltaTime, *this);
    armor.Update(deltaTime, GetFlip());
    helmet.Update(GetFlip(), target.isCrouched);

    handItem.Update(GetFlip(), target.isLookingUp);

    handItem.SetVisible(!target.isCrouched && target.stateTransition != DuckState::DEAD);
}

void DuckClientRenderer::Draw(Camera& cam) {
    Object2D::Draw(cam);
    armor.Draw(cam);
    helmet.Draw(cam);
    handItem.Draw(cam);
}

void DuckClientRenderer::OnCuack(AudioManager& audioManager) {
    audioManager.PlaySFX(duckData.cuackFileSFX);
    cuack = true;
    cuackTimer = Timer(0.2f, [this]() {
        cuack = false;

        string currentAnim = anim.GetTarget();
        size_t pos = currentAnim.find("_cuack");
        if (pos != std::string::npos) {
            currentAnim.erase(pos);
            SetTargetAnimation(currentAnim);
        }
    });
    cuackTimer.Start();
}

void DuckClientRenderer::OnDamaged(AudioManager& audioManager) {
    damaged = true;
    SetColor(Color(230, 40, 40));
    damagedTimer = Timer(0.15f, [this]() {
        damaged = false;
        SetTargetAnimation("idle");
        SetColor(skinColor);
    });
    audioManager.PlaySFX(duckData.damagedFileSFX);
    damagedTimer.Start();
}

void DuckClientRenderer::OnDead() {
    damaged = false;
    anim.SetTarget("dead");
    damagedTimer.Stop();
    SetColor(skinColor);
    handItem.SetVisible(false);

    cuackTimer.Stop();

    camController.RemoveTransform(&transform);
}

string DuckClientRenderer::GetAnimAndCuack(string animTarget) {
    if (cuack && anim.TargetExists(animTarget + "_cuack")) {
        return animTarget += "_cuack";
    }
    return animTarget;
}

void DuckClientRenderer::SetEventTarget(PlayerEvent newTarget, ResourceManager& resourceManager,
                                        AudioManager& audioManager, bool initial) {
    if (initial)
        transform.SetPos(newTarget.motion);

    fromPos = transform.GetPos();
    tLerp = 0;

    SetFlip(newTarget.flipping == Flip::Left);

    if (newTarget.cuacking)
        OnCuack(audioManager);

    switch (newTarget.stateTransition) {
        case DuckState::IDLE:
            SetTargetAnimation("idle");
            break;
        case DuckState::RUNNING:
            SetTargetAnimation("run", false);
            break;
        case DuckState::JUMPING:
            SetTargetAnimation("jumping");
            break;
        case DuckState::FALLING:
            SetTargetAnimation("falling");
            break;
        case DuckState::WOUNDED:
            OnDamaged(audioManager);
            break;
        case DuckState::DEAD:
            OnDead();
            break;
        case DuckState::DEAD_BY_FALLING:
            OnDead();
            break;
        default:
            break;
    }

    if (newTarget.isCrouched)
        SetTargetAnimation("crouched");

    armor.SetVisible(newTarget.hasArmor);
    helmet.SetVisible(newTarget.hasHelmet);

    if (target.typeOnHand != newTarget.typeOnHand) {
        handItem.SetItem(resourceManager.GetCollectableData(newTarget.typeOnHand));
    }

    target = newTarget;
}

void DuckClientRenderer::SetTargetAnimation(const string& animTarget, bool resetIndex) {
    anim.SetTarget(GetAnimAndCuack(animTarget), resetIndex);
    armor.SetAnimTarget(animTarget, resetIndex);
}
