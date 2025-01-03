#include "PlatformOptionWidget.h"

#include "editor/constantsEditor.h"
#include "multimedia/gui/GUIManager.h"

#include "constants.h"

PlatformOptionWidget::PlatformOptionWidget(GUIManager& guiManager, MapThemeData& mapThemeData,
                                           GroundDto& info, CallbackParam<MapBlock2D> onSelect):
        onSelectClicked(onSelect), gameBlock(mapThemeData, info.mySpace) {
    bool left = info.visibleEdges.find(VISIBLE_EDGES::LEFT) != info.visibleEdges.end();

    bool right = info.visibleEdges.find(VISIBLE_EDGES::RIGHT) != info.visibleEdges.end();

    bool top = info.visibleEdges.find(VISIBLE_EDGES::TOP) != info.visibleEdges.end();

    bool bottom = info.visibleEdges.find(VISIBLE_EDGES::BOTTOM) != info.visibleEdges.end();

    btn = guiManager.CreateButton(
            BUTTON_1_IMAGE,
            RectTransform(Transform(Vector2D(280, 0), Vector2D(75, 40)), Vector2D(0, 1)),
            [this]() { this->onSelectClicked(this->gameBlock); }, Color(40, 40, 40), 1);

    obj = guiManager.CreateMapBlockGUI(
            mapThemeData,
            RectTransform(Transform(info.mySpace.GetPos() * 10, info.mySpace.GetSize() * 10),
                          Vector2D(0.25, 1)),
            40);

    selectLevelText = guiManager.CreateText(
            SELECT_STR.c_str(), 30,
            RectTransform(Transform(Vector2D(280, 0), Vector2D(75, 40)), Vector2D(0, 1)),
            ColorExtension::White(), 2);

    obj->SetBorders(left, right, top, bottom);
    gameBlock.SetBorders(left, right, top, bottom);
}

void PlatformOptionWidget::DrawOption(Camera& cam) { obj->Draw(cam); }

void PlatformOptionWidget::MoveContent(Vector2D movement) {

    btn->GetRectTransform().Move(movement);
    selectLevelText->GetRectTransform().Move(movement);
    obj->GetRectTransform().Move(movement);
}
