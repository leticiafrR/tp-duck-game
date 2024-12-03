#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include <algorithm>
#include <string>
#include <vector>

#include "multimedia/Camera.h"

#include "Button.h"
#include "ButtonsManager.h"
#include "GraphicUI.h"
#include "Image.h"
#include "MapBlockGUI.h"
#include "Text.h"

class GUIManager {
private:
    std::vector<GraphicUI*> graphics;

    // std::vector<GraphicUI*> graphicsDynamic;
    ButtonsManager buttonsManager;

public:
    GUIManager();
    ~GUIManager();

    static GUIManager& GetInstance();

    const std::vector<GraphicUI*>& GetGraphics();

    void AddGUI(GraphicUI* gui);

    void RemoveGUI(GraphicUI* gui);

    void CheckSort();

    void Draw(Camera& cam);


    void HandleEvent(const SDL_Event& e, Camera& cam);

    MapBlockGUI* CreateMapBlockGUI(MapThemeData& MapThemeData, const RectTransform& rectTransform,
                                   float tileSize, int layerOrder = 0);

    Image* CreateMapBlockGUI(RectTransform rect, Color color = ColorExtension::White(),
                             int layerOrder = 0);

    Image* CreateImage(RectTransform rect, Color color = ColorExtension::White(),
                       int layerOrder = 0);

    Image* CreateImage(const string& file, RectTransform rect,
                       Color color = ColorExtension::White(), int layerOrder = 0);
    Image* CreateImage(RectTransform rect, int layerOrder = 0,
                       Color color = ColorExtension::White());
    Image* CreateImage(RectTransform rect, int layerOrder = 0, const string& file = "",
                       Color color = ColorExtension::White());

    Text* CreateText(const string& text, int fontSize = 12, RectTransform rect = RectTransform(),
                     Color color = ColorExtension::White(), int layerOrder = 0);

    Text* CreateText(RectTransform rect, int layerOrder = 0, const string& text = "",
                     int fontSize = 12, Color color = ColorExtension::White());

    Button* CreateButton(
            const string& file, RectTransform rect, Callback callback = []() {},
            Color color = ColorExtension::DarkGray(), int layerOrder = 0);

    Button* CreateButton(
            RectTransform rect, int layerOrder = 0, Callback callback = []() {},
            const string& file = BUTTON_FILE, Color color = ColorExtension::DarkGray());

    void Clear() { graphics.clear(); }

    // Remove copy
    GUIManager(const GUIManager&) = delete;
    GUIManager& operator=(const GUIManager&) = delete;
};

#endif
