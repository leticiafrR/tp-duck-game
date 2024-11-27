#include "Text.h"

Text::Text(const string& text, int fontSize, const RectTransform& rect, Color color, int layerOrder,
           const string& filename):
        GraphicUI(rect, color, layerOrder), text(text), filename(filename), fontSize(fontSize) {
    SetCanTarget(false);
}

Text::~Text() = default;

void Text::SetText(const string& newText) { text = newText; }

Font& Text::GetFont() { return FontCache::GetData(filename, fontSize); }

void Text::Draw(Camera& cam) {
    if (text.size() == 0 || !visible) {
        return;
    }
    cam.DrawText(text, GetFont(), rect, color);
}
