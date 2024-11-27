#include "ControlsScreen.h"

KeyItemGUI::KeyItemGUI(const string& key, Vector2D pos, Vector2D size, float textAngle):
        imgBg(make_shared<Image>("button_1.png", RectTransform(pos, size), Color(40, 40, 40), 11)),
        txtKey(make_shared<Text>(key, 20, RectTransform(pos, size), ColorExtension::White(), 12)) {
    txtKey->GetRectTransform().SetAngle(textAngle);
}

void KeyItemGUI::SetActive(bool visible) {
    imgBg->SetActive(visible);
    txtKey->SetActive(visible);
}

KeyItemGUI::~KeyItemGUI() = default;


void ControlsScreen::InitTexts() {
    texts.emplace_back(make_shared<Text>("Player 1", 28,
                                         RectTransform(Vector2D(-150, 400), Vector2D(200, 60)),
                                         ColorExtension::White(), 10));
    texts.emplace_back(make_shared<Text>("Player 2", 28,
                                         RectTransform(Vector2D(150, 400), Vector2D(200, 60)),
                                         ColorExtension::White(), 10));

    texts.emplace_back(make_shared<Text>("Movement", 24,
                                         RectTransform(Vector2D(-380, 300), Vector2D(200, 60)),
                                         ColorExtension::White(), 10));

    texts.emplace_back(make_shared<Text>("Look up", 24,
                                         RectTransform(Vector2D(-380, 200), Vector2D(200, 60)),
                                         ColorExtension::White(), 10));

    texts.emplace_back(make_shared<Text>("Crouch", 24,
                                         RectTransform(Vector2D(-380, 100), Vector2D(200, 60)),
                                         ColorExtension::White(), 10));

    texts.emplace_back(make_shared<Text>("Jump", 24,
                                         RectTransform(Vector2D(-380, 0), Vector2D(200, 60)),

                                         ColorExtension::White(), 10));
    texts.emplace_back(make_shared<Text>("Use item", 24,
                                         RectTransform(Vector2D(-380, -100), Vector2D(200, 60)),
                                         ColorExtension::White(), 10));
}

void ControlsScreen::InitPlayer1Keys() {
    playerKeys.emplace_back("A", Vector2D(-200, 300));
    playerKeys.emplace_back("D", Vector2D(-100, 300));

    playerKeys.emplace_back("W", Vector2D(-150, 200));
    playerKeys.emplace_back("S", Vector2D(-150, 100));

    playerKeys.emplace_back("Space", Vector2D(-150, 0), Vector2D(170, 60));

    playerKeys.emplace_back("F", Vector2D(-150, -100));
}

void ControlsScreen::InitPlayer2Keys() {
    playerKeys.emplace_back("<-", Vector2D(100, 300));
    playerKeys.emplace_back("->", Vector2D(200, 300));

    playerKeys.emplace_back("->", Vector2D(150, 200), Vector2D(60, 60), 90);
    playerKeys.emplace_back("->", Vector2D(150, 100), Vector2D(60, 60), -90);

    playerKeys.emplace_back("2", Vector2D(150, 0));

    playerKeys.emplace_back("3", Vector2D(150, -100));
}

ControlsScreen::ControlsScreen():
        imgBg(RectTransform(Vector2D::Zero(), Vector2D(2000, 2000)),
              ColorExtension::Black().SetAlpha(225), 9),
        btnBack(
                "back_icon.png", RectTransform(Vector2D(60, -60), Vector2D(70, 70), Vector2D(0, 1)),
                [this]() {
                    this->SetActive(false);
                    AudioManager::GetInstance().PlayButtonSFX();
                },
                ColorExtension::White(), 11) {

    InitTexts();

    InitPlayer1Keys();
    InitPlayer2Keys();
}

ControlsScreen::~ControlsScreen() = default;

void ControlsScreen::SetActive(bool active) {
    imgBg.SetActive(active);
    btnBack.SetActive(active);

    for (auto it: texts) {
        it->SetActive(active);
    }

    for (auto it: playerKeys) {
        it.SetActive(active);
    }
}
