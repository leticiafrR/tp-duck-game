#include "ShowColorsScreen.h"

DuckColorItemGUI::DuckColorItemGUI(Vector2D pos, const DuckClientRenderer& duck):
        imgColor("base_duck.png", RectTransform(pos, Vector2D(70, 70)), duck.GetSkinColor(), 20),
        txtNickname(duck.GetNickname(), 35,
                    RectTransform(Vector2D(pos.x + 170, pos.y), Vector2D(150, 150)),
                    ColorExtension::White(), 20) {

    imgColor.SetSourceRect(SheetDataCache::GetData("duck.yaml")["head"][0]);
}

DuckColorItemGUI::~DuckColorItemGUI() = default;

void DuckColorItemGUI::SetActive(bool active) {
    imgColor.SetActive(active);
    txtNickname.SetActive(active);
}


ShowColorsScreen::ShowColorsScreen():
        bg(RectTransform(Vector2D::Zero(), Vector2D(2000, 2000)),
           ColorExtension::Black().SetAlpha(180)),
        bgTween(bg, ColorExtension::Empty(), 0.7f, [this]() { Finish(); }),
        timer(3.0f, [this]() { bgTween.Play(); }),
        finished(true) {
    bg.SetActive(false);
}

void ShowColorsScreen::Show(map<PlayerID_t, shared_ptr<DuckClientRenderer>>& ducks) {
    finished = false;

    bg.SetActive(true);

    Vector2D initialPos(-100, 100);
    for (const auto& it: ducks) {
        ducksGUI.emplace_back(std::make_shared<DuckColorItemGUI>(initialPos, *it.second));
        initialPos += Vector2D::Down() * 80;
    }

    timer.Start();
}

ShowColorsScreen::~ShowColorsScreen() = default;

void ShowColorsScreen::Update(float deltaTime) {

    timer.Update(deltaTime);
    TweenManager::GetInstance().Update(deltaTime);
}

void ShowColorsScreen::Finish() {
    finished = true;
    bg.SetActive(false);
    for (const auto& it: ducksGUI) {
        it->SetActive(false);
    }
}
bool ShowColorsScreen::HasFinished() { return finished; }
