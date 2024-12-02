#ifndef PLAYERS_COUNT_SELECTION_H
#define PLAYERS_COUNT_SELECTION_H

#include "client/utils/GameKit.h"
#include "multimedia/Definitions.h"
#include "multimedia/gui/Button.h"
#include "multimedia/gui/Text.h"

class PlayersCountSelection {
private:
    Image imgBglocker;
    Image imgBg;

    Button btnBack;

    Text txtTitle;

    Button btnOnePlayer;
    Text txtOnePlayer;

    Button btnTwoPlayers;
    Text txtTwoPlayers;

    CallbackParam<uint8_t> onSelection;

public:
    explicit PlayersCountSelection(GameKit& gameKit);

    ~PlayersCountSelection();

    void Display(CallbackParam<uint8_t> onSelection);

    void Hide();

    void SetActive(bool active);
};

#endif
