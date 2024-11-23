#ifndef GAMEPLAY_GUI_H
#define GAMEPLAY_GUI_H

#include <string>

#include "Camera.h"
#include "ColorExtension.h"
#include "Image.h"
#include "Text.h"

class GameplayGUI {
private:
    Image imgDuck;
    Image imgHandItem;
    Text txtNickname;
    Text shadowNickname;

public:
    GameplayGUI(Color duckColor, const string& nickname):
            imgDuck("base_duck.png",
                    RectTransform(Vector2D(120, 0), Vector2D(220, 220), Vector2D::Zero(),
                                  Vector2D(0.5, 0)),
                    duckColor, 10),
            imgHandItem(RectTransform(Vector2D(150, 0), Vector2D(220, 220), Vector2D::Zero(),
                                      Vector2D(0.5, 0)),
                        ColorExtension::Empty(), 11),
            txtNickname(nickname, 25,
                        RectTransform(Vector2D(120, 15), Vector2D(220, 100), Vector2D::Zero(),
                                      Vector2D(0.5, 0)),
                        ColorExtension::White(), 13),
            shadowNickname(nickname, 25,
                           RectTransform(Vector2D(123, 14), Vector2D(220, 100), Vector2D::Zero(),
                                         Vector2D(0.5, 0)),
                           ColorExtension::Black(), 12) {
        imgDuck.SetSourceRect("duck.yaml", "head");
    }

    void SetWeapon(const string& filename) { imgHandItem.SetFile(filename); }

    ~GameplayGUI() = default;
};

#endif
