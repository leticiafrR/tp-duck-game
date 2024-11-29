#include "GraphicUI.h"

#include "multimedia/Camera.h"

#include "GUIManager.h"

GraphicUI::GraphicUI(const RectTransform& rect, Color color, int layerOrder):
        rect(rect), color(color), layerOrder(layerOrder) {
    GUIManager::GetInstance().AddGUI(this);
}

GraphicUI::~GraphicUI() { GUIManager::GetInstance().RemoveGUI(this); }

void GraphicUI::SetLayerOrder(int layerOrder) {
    this->layerOrder = layerOrder;
    GUIManager::GetInstance().CheckSort();
}
int GraphicUI::GetLayerOrder() { return layerOrder; }

void GraphicUI::SetVisible(bool visible) { this->visible = visible; }
bool GraphicUI::GetVisible() { return visible; }

void GraphicUI::SetCanTarget(bool canTarget) { this->canTarget = canTarget; }
bool GraphicUI::GetCanTarget() { return canTarget; }

void GraphicUI::SetActive(bool active) {
    SetVisible(active);
    SetCanTarget(active);
}

void GraphicUI::SetRectTransform(const RectTransform& rect) { this->rect = rect; }
RectTransform& GraphicUI::GetRectTransform() { return rect; }

Transform& GraphicUI::GetTransform() { return rect.GetTransform(); }

Vector2D GraphicUI::GetSize() { return rect.GetSize(); }
Vector2D GraphicUI::GetPos() { return rect.GetPos(); }

void GraphicUI::SetColor(Color color) { this->color = color; }
Color GraphicUI::GetColor() { return color; }

void GraphicUI::SetBase(const RectTransform& rect, Color color, int layerOrder) {
    SetRectTransform(rect);
    SetColor(color);
    SetLayerOrder(layerOrder);
}
