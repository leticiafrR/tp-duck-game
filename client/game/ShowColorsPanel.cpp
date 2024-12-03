#include "ShowColorsPanel.h"

DuckColorItemGUI::DuckColorItemGUI(GUIManager& guiManager, Vector2D pos,
                                   const PlayerData& playerData, DuckData duckData) {

    imgColor = guiManager.CreateImage(RectTransform(pos, Vector2D(70, 70)), 20, duckData.file,
                                      DUCK_SKIN_COLORS.at(playerData.playerSkin));

    txtNickname =
            guiManager.CreateText(RectTransform(Vector2D(pos.x + 170, pos.y), Vector2D(150, 150)),
                                  20, playerData.nickname, 35);

    imgColor->SetSourceRect(duckData.frames["head"][0]);
}

DuckColorItemGUI::~DuckColorItemGUI() = default;

void DuckColorItemGUI::SetActive(bool active) {
    imgColor->SetActive(active);
    txtNickname->SetActive(active);
}

ShowColorsScreen::ShowColorsScreen(GUIManager& guiManager):
        guiManager(guiManager), timer(3.0f, [this]() { bgTween.Play(); }), finished(true) {

    bg = guiManager.CreateImage(RectTransform(Vector2D::Zero(), Vector2D(2000, 2000)), 18,
                                ColorExtension::Black().SetAlpha(180));

    bgTween = ImageTween(bg, ColorExtension::Empty(), 0.7f, [this]() { Finish(); });

    bg->SetActive(false);
}

void ShowColorsScreen::Show(const unordered_map<PlayerID_t, PlayerData>& playersData,
                            DuckData duckData) {
    finished = false;

    bg->SetActive(true);

    Vector2D initialPos(-100, 100);
    for (const auto& it: playersData) {
        ducksGUI.emplace_back(guiManager, initialPos, it.second, duckData);
        initialPos += Vector2D::Down() * 80;
    }

    timer.Start();
}

ShowColorsScreen::~ShowColorsScreen() = default;

void ShowColorsScreen::Update(float deltaTime) {

    timer.Update(deltaTime);
    bgTween.Update(deltaTime);
    // TweenManager::GetInstance().Update(deltaTime);
}

void ShowColorsScreen::Finish() {
    finished = true;
    bg->SetActive(false);
    for (auto& it: ducksGUI) {
        it.SetActive(false);
    }
}
bool ShowColorsScreen::HasFinished() { return finished; }
