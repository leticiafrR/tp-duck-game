#include "GameplayGUI.h"

LocalPlayerGUI::LocalPlayerGUI(Color duckColor, const string& nickname, bool isOne):
        imgDuck("base_duck.png",
                RectTransform(Vector2D(120, 0), Vector2D(210, 210), Vector2D::Zero(),
                              Vector2D(0.5, 0)),
                duckColor, 10),
        imgHandItem("",
                    RectTransform(Vector2D(150, 0), Vector2D(220, 220), Vector2D::Zero(),
                                  Vector2D(0.5, 0)),
                    ColorExtension::Empty(), 11),
        txtNickname(nickname, 30,
                    RectTransform(Vector2D(120, 15), Vector2D(240, 110), Vector2D::Zero(),
                                  Vector2D(0.5, 0)),
                    ColorExtension::White(), 13),
        shadowNickname(nickname, 30,
                       RectTransform(Vector2D(124, 13), Vector2D(240, 110), Vector2D::Zero(),
                                     Vector2D(0.5, 0)),
                       ColorExtension::Black(), 12) {

    if (!isOne) {
        imgDuck.SetFlip(true);
        imgHandItem.SetFlip(true);
        imgDuck.SetRectTransform(RectTransform(Vector2D(-120, 0), Vector2D(210, 210),
                                               Vector2D(1, 0), Vector2D(0.5, 0)));
        imgHandItem.SetRectTransform(RectTransform(Vector2D(-150, 0), Vector2D(210, 210),
                                                   Vector2D(1, 0), Vector2D(0.5, 0)));
        txtNickname.SetRectTransform(RectTransform(Vector2D(-120, 15), Vector2D(210, 210),
                                                   Vector2D(1, 0), Vector2D(0.5, 0)));
        shadowNickname.SetRectTransform(RectTransform(Vector2D(-118, 12), Vector2D(210, 210),
                                                      Vector2D(1, 0), Vector2D(0.5, 0)));
    }
    imgDuck.SetSourceRect("duck.yaml", "head");
    imgHandItem.SetVisible(false);
}

LocalPlayerGUI::~LocalPlayerGUI() = default;

void LocalPlayerGUI::SetHandItem(TypeCollectable type) {
    imgHandItem.SetFile(itemsMap.at(type).imageFile);
    imgHandItem.SetSourceRect(itemsMap.at(type).GetSourceRect());
    imgDuck.SetVisible(true);
}
void LocalPlayerGUI::RemoveHandItem() { imgHandItem.SetVisible(false); }


GameplayGUI::GameplayGUI() {}
GameplayGUI::~GameplayGUI() = default;

void GameplayGUI::InitPlayer1GUI(Color color, const string& nickname) {
    player1GUI = make_shared<LocalPlayerGUI>(color, nickname, true);
}
void GameplayGUI::InitPlayer2GUI(Color color, const string& nickname) {
    player2GUI = make_shared<LocalPlayerGUI>(color, nickname, false);
}
void GameplayGUI::SetPlayer1Weapon(TypeCollectable type) { player1GUI->SetHandItem(type); }
void GameplayGUI::SetPlayer2Weapon(TypeCollectable type) { player2GUI->SetHandItem(type); }
