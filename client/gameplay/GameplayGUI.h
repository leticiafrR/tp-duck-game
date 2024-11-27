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
    LocalPlayerGUI(Color duckColor, const string& nickname, bool isOne);
    ~LocalPlayerGUI();
    void SetHandItem(TypeCollectable type);
    void RemoveHandItem();
};

class GameplayGUI {
private:
    shared_ptr<LocalPlayerGUI> player1GUI;
    shared_ptr<LocalPlayerGUI> player2GUI;

public:
    GameplayGUI();
    ~GameplayGUI();

    void InitPlayer1GUI(Color color, const string& nickname);

    void InitPlayer2GUI(Color color, const string& nickname);
    void SetPlayer1Weapon(TypeCollectable type);
    void SetPlayer2Weapon(TypeCollectable type);
};

#endif
