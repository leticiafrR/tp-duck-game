#include "GameGUI.h"

LocalPlayerGUI::LocalPlayerGUI(GUIManager& guiManager, DuckData duckData, Color duckColor,
                               const string& nickname, bool isOne) {

    Image* imgDuck = guiManager.CreateImage(
            RectTransform(Vector2D(120, 0), Vector2D(210, 210), Vector2D::Zero(), Vector2D(0.5, 0)),
            10, duckData.file, duckColor);

    imgDuck->SetSourceRect(duckData.frames["head"][0]);


    Text* txtNickname = guiManager.CreateText(RectTransform(Vector2D(120, 15), Vector2D(240, 110),
                                                            Vector2D::Zero(), Vector2D(0.5, 0)),
                                              13, nickname, 30);
    Text* shadowNickname =
            guiManager.CreateText(RectTransform(Vector2D(124, 13), Vector2D(240, 110),
                                                Vector2D::Zero(), Vector2D(0.5, 0)),
                                  12, nickname, 30, ColorExtension::Black());
    if (!isOne) {
        imgDuck->SetFlip(true);
        imgDuck->SetRectTransform(RectTransform(Vector2D(-120, 0), Vector2D(210, 210),
                                                Vector2D(1, 0), Vector2D(0.5, 0)));
        txtNickname->SetRectTransform(RectTransform(Vector2D(-120, 15), Vector2D(210, 210),
                                                    Vector2D(1, 0), Vector2D(0.5, 0)));
        shadowNickname->SetRectTransform(RectTransform(Vector2D(-118, 12), Vector2D(210, 210),
                                                       Vector2D(1, 0), Vector2D(0.5, 0)));
    }
}

LocalPlayerGUI::~LocalPlayerGUI() = default;

GameplayGUI::GameplayGUI(GUIManager& guiManager, DuckData duckData):
        guiManager(guiManager),
        duckData(duckData),
        player1GUI(std::nullopt),
        player2GUI(std::nullopt) {}

GameplayGUI::~GameplayGUI() = default;

void GameplayGUI::InitPlayer1GUI(Color color, const string& nickname) {
    player1GUI = LocalPlayerGUI(guiManager, duckData, color, nickname, true);
}
void GameplayGUI::InitPlayer2GUI(Color color, const string& nickname) {
    player2GUI = LocalPlayerGUI(guiManager, duckData, color, nickname, false);
}
