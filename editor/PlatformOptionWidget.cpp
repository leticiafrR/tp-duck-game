#include "PlatformOptionWidget.h"

#include "constants.h"

PlatformOptionWidget::PlatformOptionWidget(GroundDto& info, CallbackParam<vector<string>> onSelect):
        obj(BLOCK_MAP, BLOCK_MAP_YAML, info.mySpace, 4),
        btn(
                BUTTON_1_IMAGE,
                RectTransform(Transform(Vector2D(280, 0), Vector2D(100, 20)), Vector2D(0, 1)),
                [this]() {
                    std::cout << "Boton presionado " << std::endl;
                    this->onSelectClicked(this->edges);
                },
                Color(40, 40, 40), 1),
        selectLevelText(
                SELECT_STR.c_str(), 30,
                RectTransform(Transform(Vector2D(280, 0), Vector2D(100, 20)), Vector2D(0, 1)),
                ColorExtension::White(), 2),
        onSelectClicked(onSelect) {
    bool left = false, right = false, top = false, bottom = false;
    if (info.visibleEdges.find(VISIBLE_EDGES::LEFT) != info.visibleEdges.end()) {
        left = true;
        edges.emplace_back(LEFT_STR);
    }

    if (info.visibleEdges.find(VISIBLE_EDGES::RIGHT) != info.visibleEdges.end()) {
        right = true;
        edges.emplace_back(RIGHT_STR);
    }

    if (info.visibleEdges.find(VISIBLE_EDGES::TOP) != info.visibleEdges.end()) {
        top = true;
        edges.emplace_back(TOP_STR);
    }

    if (info.visibleEdges.find(VISIBLE_EDGES::BOTTOM) != info.visibleEdges.end()) {
        bottom = true;
        edges.emplace_back(BOTTOM_STR);
    }

    obj.SetBorders(left, right, top, bottom);
}

void PlatformOptionWidget::DrawOption(Camera& cam) { obj.Draw(cam); }


void PlatformOptionWidget::MoveContent(Vector2D movement, Vector2D movObj) {

    btn.GetRectTransform().Move(movement);
    selectLevelText.GetRectTransform().Move(movement);
    std::cout << btn.GetRectTransform().GetTransform().ToString() << std::endl;
    Transform& t = obj.GetTransform();
    t.SetPos(movObj);
    std::cout << obj.GetTransform().GetPos().x << " " << obj.GetTransform().GetPos().y << std::endl;
}
