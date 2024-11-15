#ifndef TEXT_H
#define TEXT_H

#include <string>

#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/SDLTTF.hh>

#include "Camera.h"
#include "FontCache.h"
#include "RectTransform.h"

using std::string;
using namespace SDL2pp;  // NOLINT

class Text {
private:
    string text;
    string filename;
    int fontSize;
    RectTransform rectTransform;
    Color color;

public:
    Text(const string& text, int fontSize, RectTransform rectTransform, Color color,
         const string& filename = "pixel.ttf"):
            text(text),
            filename(filename),
            fontSize(fontSize),
            rectTransform(rectTransform),
            color(color) {}

    void SetText(const string& newText) { text = newText; }

    RectTransform& GetRectTransform() { return rectTransform; }
    Font& GetFont() { return FontCache::GetData(filename, fontSize); }

    void Draw(Camera& cam) {
        if (text.size() == 0) {
            return;
        }
        cam.DrawText(text, GetFont(), rectTransform, color);
    }

    ~Text() = default;
};

#endif
