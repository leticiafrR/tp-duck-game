#ifndef GAMEPLAY_GUI_H
#define GAMEPLAY_GUI_H

#include <memory>
#include <string>
#include <unordered_map>

#include "client/rendering/SpriteRendererData.h"
#include "data/snapshot.h"
#include "multimedia/Camera.h"
#include "multimedia/ColorExtension.h"
#include "multimedia/Image.h"
#include "multimedia/Text.h"

using std::make_shared;
using std::shared_ptr;
using std::string;
using std::unordered_map;

class LocalPlayerGUI {
private:
    const unordered_map<TypeCollectable, SpriteRendererData> itemsMap = {
            {TypeCollectable::EMPTY, SpriteRendererData("", "", "")},
            {TypeCollectable::COWBOY_PISTOL,
             SpriteRendererData("pistols.png", "pistols.yaml", "cowboy_pistol",
                                Vector2D(0, -0.4f))},
            {TypeCollectable::LASER_RIFLE,
             SpriteRendererData("laser.png", "laser.yaml", "laser_rifle", Vector2D(0, -0.5f))},
            {TypeCollectable::ARMOR, SpriteRendererData("", "", "")},
            {TypeCollectable::HELMET, SpriteRendererData("", "", "")}};

    Image imgDuck;
    Image imgHandItem;
    Text txtNickname;
    Text shadowNickname;

public:
    LocalPlayerGUI(Color duckColor, const string& nickname, bool isOne):
            imgDuck("base_duck.png",
                    RectTransform(Vector2D(120, 0), Vector2D(210, 210), Vector2D::Zero(),
                                  Vector2D(0.5, 0)),
                    duckColor, 10),
            imgHandItem("",
                        RectTransform(Vector2D(150, 0), Vector2D(220, 220), Vector2D::Zero(),
                                      Vector2D(0.5, 0)),
                        ColorExtension::Empty(), 11),
            txtNickname(nickname, 30,
                        RectTransform(Vector2D(120, 15), Vector2D(240, 110), Vector2D::Zero(),
                                      Vector2D(0.5, 0)),
                        ColorExtension::White(), 13),
            shadowNickname(nickname, 30,
                           RectTransform(Vector2D(124, 13), Vector2D(240, 110), Vector2D::Zero(),
                                         Vector2D(0.5, 0)),
                           ColorExtension::Black(), 12) {

        if (!isOne) {
            imgDuck.SetFlip(true);
            imgHandItem.SetFlip(true);
            imgDuck.SetRectTransform(RectTransform(Vector2D(-120, 0), Vector2D(210, 210),
                                                   Vector2D(1, 0), Vector2D(0.5, 0)));
            imgHandItem.SetRectTransform(RectTransform(Vector2D(-150, 0), Vector2D(210, 210),
                                                       Vector2D(1, 0), Vector2D(0.5, 0)));
            txtNickname.SetRectTransform(RectTransform(Vector2D(-120, 15), Vector2D(210, 210),
                                                       Vector2D(1, 0), Vector2D(0.5, 0)));
            shadowNickname.SetRectTransform(RectTransform(Vector2D(-118, 12), Vector2D(210, 210),
                                                          Vector2D(1, 0), Vector2D(0.5, 0)));
        }
        imgDuck.SetSourceRect("duck.yaml", "head");
        imgHandItem.SetVisible(false);
    }
    void SetHandItem(TypeCollectable type) {
        imgHandItem.SetFile(itemsMap.at(type).imageFile);
        imgHandItem.SetSourceRect(itemsMap.at(type).GetSourceRect());
        imgDuck.SetVisible(true);
    }
    void RemoveHandItem() { imgHandItem.SetVisible(false); }


    ~LocalPlayerGUI() = default;
};

class GameplayGUI {
private:
    shared_ptr<LocalPlayerGUI> player1GUI;
    shared_ptr<LocalPlayerGUI> player2GUI;

public:
    GameplayGUI() {}

    void InitPlayer1GUI(Color color, const string& nickname) {
        player1GUI = make_shared<LocalPlayerGUI>(color, nickname, true);
    }
    void InitPlayer2GUI(Color color, const string& nickname) {
        player2GUI = make_shared<LocalPlayerGUI>(color, nickname, false);
    }
    void SetPlayer1Weapon(TypeCollectable type) { player1GUI->SetHandItem(type); }
    void SetPlayer2Weapon(TypeCollectable type) { player2GUI->SetHandItem(type); }

    ~GameplayGUI() = default;
};

#endif
