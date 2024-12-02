#ifndef GRAPHIC_UI_H
#define GRAPHIC_UI_H

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "multimedia/Camera.h"
#include "multimedia/ColorExtension.h"

#include "RectTransform.h"

class GraphicUI {
protected:
    RectTransform rect;
    Color color = ColorExtension::Empty();
    int layerOrder = 0;
    bool canTarget = true;
    bool visible = true;

public:
    GraphicUI(const RectTransform& rect = RectTransform(), Color color = ColorExtension::White(),
              int layerOrder = 0);

    virtual ~GraphicUI();

    virtual void Draw(Camera& cam) = 0;

    void SetLayerOrder(int layerOrder);
    int GetLayerOrder();

    void SetVisible(bool visible);
    bool GetVisible();

    void SetCanTarget(bool target);
    bool GetCanTarget();

    void SetActive(bool visible);

    void SetRectTransform(const RectTransform& rect);
    RectTransform& GetRectTransform();

    Transform& GetTransform();
    Vector2D GetSize();
    Vector2D GetPos();

    void SetColor(Color color);
    Color GetColor();

    void SetBase(const RectTransform& rect, Color color = ColorExtension::White(),
                 int layerOrder = 0);
};

#endif
