#include "ControlsScreen.h"

KeyItemGUI::KeyItemGUI(GUIManager& guiManager, const string& key, Vector2D pos, Vector2D size,
                       float textAngle) {
    imgBg = guiManager.CreateImage(RectTransform(pos, size), 11, BUTTON_FILE,
                                   ColorExtension::DarkGray());
    txtKey = guiManager.CreateText(RectTransform(pos, size), 12, key, 20);

    txtKey->GetRectTransform().SetAngle(textAngle);
}

void KeyItemGUI::SetActive(bool visible) {
    imgBg->SetActive(visible);
    txtKey->SetActive(visible);
}

KeyItemGUI::~KeyItemGUI() = default;


void ControlsScreen::AddText(string text, int x, int y) {
    texts.push_back(
            guiManager.CreateText(RectTransform(Vector2D(x, y), Vector2D(200, 60)), 10, text, 24));
}

void ControlsScreen::InitTexts() {
    AddText("Player 1", -150, 400);
    AddText("Player 2", 150, 400);

    AddText("Movement", -380, 300);
    AddText("Look up", -380, 200);
    AddText("Crouch", -380, 100);
    AddText("Jump", -380, 0);
    AddText("Use item", -380, -100);
    AddText("Pick up item", -380, -200);
    AddText("Drop item", -380, -300);
    AddText("Cuack", -380, -400);
}

void ControlsScreen::AddPlayerKey(string key, Vector2D pos, Vector2D size, float textAngle) {
    playerKeys.emplace_back(guiManager, key, pos, size, textAngle);
}

void ControlsScreen::InitPlayer1Keys() {
    AddPlayerKey("A", Vector2D(-200, 300));
    AddPlayerKey("D", Vector2D(-100, 300));

    AddPlayerKey("W", Vector2D(-150, 200));
    AddPlayerKey("S", Vector2D(-150, 100));

    AddPlayerKey("Space", Vector2D(-150, 0), Vector2D(170, 60));

    AddPlayerKey("F", Vector2D(-150, -100));

    AddPlayerKey("E", Vector2D(-150, -200));

    AddPlayerKey("G", Vector2D(-150, -300));

    AddPlayerKey("C", Vector2D(-150, -400));
}

void ControlsScreen::InitPlayer2Keys() {
    AddPlayerKey("<-", Vector2D(100, 300));
    AddPlayerKey("->", Vector2D(200, 300));

    AddPlayerKey("->", Vector2D(150, 200), Vector2D(60, 60), 90);
    AddPlayerKey("->", Vector2D(150, 100), Vector2D(60, 60), -90);

    AddPlayerKey("R-Shift", Vector2D(150, 0), Vector2D(170, 60));

    AddPlayerKey("J", Vector2D(150, -100));

    AddPlayerKey("K", Vector2D(150, -200));

    AddPlayerKey("L", Vector2D(150, -300));

    AddPlayerKey("O", Vector2D(150, -400));
}

ControlsScreen::ControlsScreen(AudioManager& audioPlayer, GUIManager& guiManager):
        guiManager(guiManager) {

    imgBg = guiManager.CreateImage(RectTransform(Vector2D::Zero(), Vector2D(2000, 2000)), 9,
                                   ColorExtension::Black().SetAlpha(225));
    btnBack = guiManager.CreateButton(
            RectTransform(Vector2D(60, -60), Vector2D(70, 70), Vector2D(0, 1)), 11,
            [this, &audioPlayer]() {
                this->SetActive(false);
                audioPlayer.PlayButtonSFX();
            },
            BACK_BUTTON_FILE, ColorExtension::White());

    InitTexts();

    InitPlayer1Keys();
    InitPlayer2Keys();
}

ControlsScreen::~ControlsScreen() = default;

void ControlsScreen::SetActive(bool active) {
    imgBg->SetActive(active);
    btnBack->SetActive(active);

    for (auto& it: texts) {
        it->SetActive(active);
    }

    for (auto& it: playerKeys) {
        it.SetActive(active);
    }
}
