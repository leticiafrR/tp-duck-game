#include "GraphicUI.h"

#include "Camera.h"
#include "GUIManager.h"

GraphicUI::GraphicUI(int layerOrder): layerOrder(layerOrder) {
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
