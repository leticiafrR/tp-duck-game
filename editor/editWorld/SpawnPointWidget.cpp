#include "SpawnPointWidget.h"

#include "editor/constantsEditor.h"

#include "constants.h"

SpawnPointWidget::SpawnPointWidget(CallbackParam<pair<Object2D, int>> onSelect, int _type,
                                   const std::string& fileName, Vector2D pos,
                                   const std::string& text, Vector2D size):
        btn(
                BUTTON_1_IMAGE,
                RectTransform(Transform(Vector2D(pos.x, pos.y), Vector2D(75, 40)),
                              Vector2D(0.5, 1)),
                [this]() { this->onSelectClicked(pair<Object2D, int>(this->point, this->type)); },
                Color(40, 40, 40), 1),
        selectLevelText(text.c_str(), 30,
                        RectTransform(Transform(Vector2D(pos.x, pos.y), Vector2D(75, 40)),
                                      Vector2D(0.5, 1)),
                        ColorExtension::White(), 2),
        onSelectClicked(onSelect),
        img(fileName,
            RectTransform(Transform(Vector2D(pos.x + 50, pos.y), Vector2D(size.x, size.y)),
                          Vector2D(0.5, 1)),
            Color(160, 160, 160), 0),
        point(fileName, Transform(Vector2D(0, 0), Vector2D(2, 2)), Color(40, 40, 40)),
        type(_type) {}

void SpawnPointWidget::MoveContent(Vector2D movement) {

    btn.GetRectTransform().Move(movement);
    selectLevelText.GetRectTransform().Move(movement);
    point.GetTransform().SetPos(movement);
}

void SpawnPointWidget::Draw(Camera& cam) { img.Draw(cam); }
