#include "LevelWidget.h"


LevelWidget::LevelWidget(const string& ownerName, CallbackParam<string> onSelect):
        levelName(ownerName),
        lvlConentImage(
                RectTransform(Transform(Vector2D(0, 0), Vector2D(900, 120)), Vector2D(0.5, 1)),
                Color(160, 160, 160), 0),
        lvlNameText(
                ownerName, 30,
                RectTransform(Transform(Vector2D(-280, 0), Vector2D(300, 120)), Vector2D(0.5, 1)),
                ColorExtension::White(), 1),
        selectLevelButton(
                "button_1.png",
                RectTransform(Transform(Vector2D(280, 0), Vector2D(150, 80)), Vector2D(0.5, 1)),
                [this]() { this->onSelectClicked(this->levelName); }, Color(40, 40, 40), 1),
        selectLevelText(
                SELECT_STR.c_str(), 30,
                RectTransform(Transform(Vector2D(280, 0), Vector2D(150, 80)), Vector2D(0.5, 1)),
                ColorExtension::White(), 2),
        onSelectClicked(onSelect) {}


void LevelWidget::MoveContent(Vector2D movement) {
    lvlConentImage.GetRectTransform().Move(movement);

    lvlNameText.GetRectTransform().Move(movement);

    selectLevelButton.GetRectTransform().Move(movement);
    selectLevelText.GetRectTransform().Move(movement);
}
