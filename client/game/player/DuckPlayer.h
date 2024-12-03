#ifndef DUCK_PLAYER_H
#define DUCK_PLAYER_H

#include <map>
#include <string>

#include "client/Framework.h"
#include "client/game/CameraController.h"
#include "data/dataTransferObjects.h"
#include "data/snapshot.h"

#include "Armor.h"
#include "HandItem.h"
#include "Helmet.h"

class DuckClientRenderer: public Object2D {
private:
    Timer damagedTimer;
    Timer cuackTimer;
    Color skinColor;
    std::string nickname;
    bool damaged = false;
    bool cuack = false;

public:
    DuckData duckData;
    CameraController& camController;
    Animator anim;

    Vector2D fromPos;
    float tLerp = 0;

    PlayerEvent target;

    HandItem handItem;

    Armor armor;
    HelmetRenderer helmet;

    DuckClientRenderer(Vector2D size, Color skinColor, ResourceManager& resourceManager,
                       CameraController& camController);

    ~DuckClientRenderer();

    Color GetSkinColor() const;
    std::string GetNickname() const;

    void Update(float deltaTime);

    void Draw(Camera& cam) override;

    Transform& GetTransform();

    void OnCuack(AudioManager& audioManager);

    void OnDamaged(AudioManager& audioManager);

    void OnDead();

    void SetTargetAnimation(const string& animTarget, bool resetIndex = true);

    string GetAnimAndCuack(string animTarget);

    void SetEventTarget(PlayerEvent newTarget, ResourceManager& resourceManager,
                        AudioManager& audioManager, bool initial = false);
};

#endif
