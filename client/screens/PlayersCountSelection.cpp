#include "PlayersCountSelection.h"

PlayersCountSelection::PlayersCountSelection():
        imgBglocker(RectTransform(Vector2D::Zero(), Vector2D(2000, 2000)),
                    ColorExtension::Black().SetAlpha(100), 9),
        imgBg(RectTransform(Vector2D::Zero(), Vector2D(600, 600)),
              ColorExtension::Black().SetAlpha(225), 9),
        btnBack(
                "back_icon.png", RectTransform(Vector2D(60, -60), Vector2D(70, 70), Vector2D(0, 1)),
                [this]() {
                    this->Hide();
                    AudioManager::GetInstance().PlayButtonSFX();
                },
                ColorExtension::White(), 11),
        txtTitle("Local players selection", 30, RectTransform(Vector2D(0, 200), Vector2D(500, 100)),
                 ColorExtension::White(), 11),
        btnOnePlayer(
                "button_1.png", RectTransform(Vector2D(0, 50), Vector2D(200, 80)),
                [this]() {
                    this->Hide();
                    this->onSelection(1);
                },
                Color(40, 40, 40), 11),
        txtOnePlayer("One Player", 24, RectTransform(Vector2D(0, 50), Vector2D(200, 80)),
                     ColorExtension::White(), 12),
        btnTwoPlayers(
                "button_1.png", RectTransform(Vector2D(0, -50), Vector2D(200, 80)),
                [this]() {
                    this->Hide();
                    this->onSelection(2);
                },
                Color(40, 40, 40), 11),
        txtTwoPlayers("Two Players", 24, RectTransform(Vector2D(0, -50), Vector2D(200, 80)),
                      ColorExtension::White(), 12) {
    Hide();
}

PlayersCountSelection::~PlayersCountSelection() = default;

void PlayersCountSelection::Display(CallbackParam<uint8_t> onSelection) {
    this->onSelection = onSelection;
    SetActive(true);
}

void PlayersCountSelection::Hide() { SetActive(false); }

void PlayersCountSelection::SetActive(bool active) {
    imgBglocker.SetActive(active);
    imgBg.SetActive(active);
    txtTitle.SetActive(active);
    btnBack.SetActive(active);
    btnOnePlayer.SetActive(active);
    btnTwoPlayers.SetActive(active);

    txtOnePlayer.SetVisible(active);
    txtTwoPlayers.SetVisible(active);
}
