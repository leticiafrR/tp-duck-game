#include "GUIManager.h"

#include <string>

using std::string;

GUIManager::GUIManager() {}

GUIManager::~GUIManager() {
    for (auto g: graphics) {
        delete g;
    }
}

void GUIManager::AddGUI(GraphicUI* gui) {
    gui->onLayerChanged = [this]() { CheckSort(); };
    graphics.push_back(gui);
    CheckSort();
}

void GUIManager::RemoveGUI(GraphicUI* gui) {
    auto it = std::find(graphics.begin(), graphics.end(), gui);
    if (it != graphics.end()) {
        graphics.erase(it);
    }
    CheckSort();
}

void GUIManager::CheckSort() {
    bool sorted = std::is_sorted(graphics.begin(), graphics.end(), [](GraphicUI* a, GraphicUI* b) {
        return a->GetLayerOrder() < b->GetLayerOrder();
    });

    if (!sorted) {
        std::sort(graphics.begin(), graphics.end(), [](GraphicUI* a, GraphicUI* b) {
            return a->GetLayerOrder() < b->GetLayerOrder();
        });
    }
}

void GUIManager::Draw(Camera& cam) {
    for (auto gui: graphics) {
        if (!gui->GetVisible())
            continue;
        gui->Draw(cam);
    }
}

void GUIManager::HandleEvent(const SDL_Event& e, Camera& cam) {
    buttonsManager.HandleEvent(e, cam, graphics);
}

MapBlockGUI* GUIManager::CreateMapBlockGUI(MapThemeData& MapThemeData, const RectTransform& rect,
                                           float tileSize, int layerOrder) {
    MapBlockGUI* mapBlock = new MapBlockGUI(MapThemeData, rect, tileSize, layerOrder);
    AddGUI(mapBlock);
    return mapBlock;
}

Image* GUIManager::CreateImage(const string& file, RectTransform rect, Color color,
                               int layerOrder) {
    return CreateImage(rect, layerOrder, file, color);
}

Image* GUIManager::CreateImage(RectTransform rect, int layerOrder, const string& file,
                               Color color) {
    Image* image = new Image(file, rect, color, layerOrder);
    AddGUI(image);
    return image;
}

Image* GUIManager::CreateImage(RectTransform rect, Color color, int layerOrder) {
    Image* image = new Image(rect, color, layerOrder);
    AddGUI(image);
    return image;
}

Image* GUIManager::CreateImage(RectTransform rect, int layerOrder, Color color) {
    Image* image = new Image(rect, color, layerOrder);
    AddGUI(image);
    return image;
}

Text* GUIManager::CreateText(const string& text, int fontSize, RectTransform rect, Color color,
                             int layerOrder) {
    return CreateText(rect, layerOrder, text, fontSize, color);
}

Text* GUIManager::CreateText(RectTransform rect, int layerOrder, const string& textStr,
                             int fontSize, Color color) {
    Text* text = new Text(textStr, fontSize, rect, color, layerOrder);
    AddGUI(text);
    return text;
}

Button* GUIManager::CreateButton(const string& file, RectTransform rect, Callback callback,
                                 Color color, int layerOrder) {
    return CreateButton(rect, layerOrder, callback, file, color);
}

Button* GUIManager::CreateButton(RectTransform rect, int layerOrder, Callback callback,
                                 const string& file, Color color) {
    Button* button = new Button(file, rect, callback, color, layerOrder);
    AddGUI(button);
    buttonsManager.AddButton(button);

    return button;
}
