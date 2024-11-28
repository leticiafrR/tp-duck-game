#include "DuckClientRenderer.h"

const std::map<uint8_t, Color> DuckClientRenderer::SkinColors = {
        {0, ColorExtension::White()}, {1, ColorExtension::Yellow()},
        {2, ColorExtension::Blue()},  {3, ColorExtension::Orange()},
        {4, ColorExtension::Cyan()},  {5, ColorExtension::Purple()}};

Color DuckClientRenderer::GetColorById(uint8_t id) { return SkinColors.at(id); }

DuckClientRenderer::DuckClientRenderer(const Transform& transform, PlayerData data,
                                       PlayerEvent initialEvent, CameraController& camController):
        Object2D("base_duck.png", transform),
        camController(camController),
        anim(*this, "duck.yaml", "idle", 22),
        fromPos(transform.GetPos()),
        target(initialEvent),
        handItem(this->transform, initialEvent.typeOnHand),
        chestplate(this->transform, 22),
        helmet(this->transform) {

    this->transform.SetSize(transform.GetSize() * 1.4);  // Size rendering offset

    SetEventTarget(target);
    skinColor = SkinColors.at(data.playerSkin);
    SetColor(skinColor);
    nickname = data.nickname;
    camController.AddTransform(&this->transform);
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

    anim.Update(deltaTime);
    chestplate.Update(deltaTime, GetFlip());
    helmet.Update(GetFlip(), target.isCrouched);

    handItem.Update(GetFlip(), target.isLookingUp);

    handItem.SetVisible(!target.isCrouched && target.stateTransition != DuckState::DEAD);
}

void DuckClientRenderer::Draw(Camera& cam) {
    Object2D::Draw(cam);
    chestplate.Draw(cam);
    helmet.Draw(cam);
    handItem.Draw(cam);
}

void DuckClientRenderer::OnCuack() {
    AudioManager::GetInstance().PlayCuackSFX();
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

void DuckClientRenderer::OnDamaged() {
    damaged = true;
    SetColor(Color(230, 40, 40));
    damagedTimer = Timer(0.15f, [this]() {
        damaged = false;
        SetTargetAnimation("idle");
        SetColor(skinColor);
    });
    AudioManager::GetInstance().PlayDamagedSFX();
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

void DuckClientRenderer::SetEventTarget(PlayerEvent newTarget) {
    fromPos = transform.GetPos();
    tLerp = 0;
    target = newTarget;

    SetFlip(target.flipping == Flip::Left);

    if (target.cuacking)
        OnCuack();

    switch (target.stateTransition) {
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
            OnDamaged();
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

    chestplate.SetVisible(target.hasArmor);
    helmet.SetVisible(target.hasHelmet);

    handItem.SetItem(target.typeOnHand);
}

void DuckClientRenderer::SetTargetAnimation(const string& animTarget, bool resetIndex) {
    anim.SetTarget(GetAnimAndCuack(animTarget), resetIndex);
    chestplate.SetAnimTarget(animTarget, resetIndex);
}
