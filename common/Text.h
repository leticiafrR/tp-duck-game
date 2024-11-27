#ifndef TEXT_H
#define TEXT_H

#include <string>

#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/SDLTTF.hh>

#include "Camera.h"
#include "FontCache.h"
#include "GraphicUI.h"
#include "RectTransform.h"

using std::string;
using namespace SDL2pp;  // NOLINT

class Text: public GraphicUI {
private:
    string text = "";
    string filename = "pixel.ttf";
    int fontSize = 0;

public:
    Text(const string& text, int fontSize, const RectTransform& rect, Color color,
         int layerOrder = 0, const string& filename = "pixel.ttf"):
            GraphicUI(rect, color, layerOrder), text(text), filename(filename), fontSize(fontSize) {
        SetCanTarget(false);
    }

    void SetText(const string& newText) { text = newText; }

    Font& GetFont() { return FontCache::GetData(filename, fontSize); }

    void Draw(Camera& cam) override {
        if (text.size() == 0 || !visible) {
            return;
        }
        cam.DrawText(text, GetFont(), rect, color);
    }

    ~Text() = default;
};

#endif