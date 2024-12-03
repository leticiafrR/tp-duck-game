#include "PlayersCountSelection.h"

void PlayersCountSelection::InitPanel(AudioManager& audioPlayer, GUIManager& guiManager) {
    items.push_back(guiManager.CreateImage(RectTransform(Vector2D::Zero(), Vector2D(2000, 2000)), 9,
                                           ColorExtension::Black().SetAlpha(100)));

    items.push_back(guiManager.CreateImage(RectTransform(Vector2D::Zero(), Vector2D(600, 600)), 10,
                                           ColorExtension::Black().SetAlpha(225)));

    items.push_back(guiManager.CreateButton(
            RectTransform(Vector2D(60, -60), Vector2D(70, 70), Vector2D(0, 1)), 11,
            [this, &audioPlayer]() {
                this->Hide();
                audioPlayer.PlayButtonSFX();
            },
            BACK_BUTTON_FILE, ColorExtension::White()));

    items.push_back(guiManager.CreateText(RectTransform(Vector2D(0, 200), Vector2D(500, 100)), 11,
                                          "Local players selection", 30));
}

void PlayersCountSelection::InitOnePlayerButton(AudioManager& audioPlayer, GUIManager& guiManager) {
    items.push_back(guiManager.CreateButton(RectTransform(Vector2D(0, 50), Vector2D(200, 80)), 11,
                                            [this, &audioPlayer]() {
                                                this->Hide();
                                                this->onSelection(1);
                                                audioPlayer.PlayButtonSFX();
                                            }));

    items.push_back(guiManager.CreateText(RectTransform(Vector2D(0, 50), Vector2D(200, 80)), 12,
                                          "One Player", 24));
}

void PlayersCountSelection::InitSecondPlayerButton(AudioManager& audioPlayer,
                                                   GUIManager& guiManager) {
    items.push_back(guiManager.CreateButton(RectTransform(Vector2D(0, -50), Vector2D(200, 80)), 11,
                                            [this, &audioPlayer]() {
                                                this->Hide();
                                                this->onSelection(2);
                                                audioPlayer.PlayButtonSFX();
                                            }));

    items.push_back(guiManager.CreateText(RectTransform(Vector2D(0, -50), Vector2D(200, 80)), 12,
                                          "Two Players", 24));
}

PlayersCountSelection::PlayersCountSelection(AudioManager& audioPlayer, GUIManager& guiManager) {
    InitPanel(audioPlayer, guiManager);
    InitOnePlayerButton(audioPlayer, guiManager);
    InitSecondPlayerButton(audioPlayer, guiManager);
    Hide();
}

PlayersCountSelection::~PlayersCountSelection() = default;

void PlayersCountSelection::Display(CallbackParam<uint8_t> onSelection) {
    this->onSelection = onSelection;
    SetActive(true);
}

void PlayersCountSelection::Hide() { SetActive(false); }

void PlayersCountSelection::SetActive(bool active) {
    for (auto item: items) {
        item->SetActive(active);
    }
}
