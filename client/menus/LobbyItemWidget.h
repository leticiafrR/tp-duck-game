#ifndef LOBBY_ITEM_WIDGET_H
#define LOBBY_ITEM_WIDGET_H
#include <string>

#include "client/Framework.h"
#include "client/FrameworkUI.h"

using std::string;

class LobbyItemWidget {
private:
public:
    int lobbyId;
    Image* matchConentImage;
    Text* matchOwnerText;
    Text* matchPlayersText;
    Button* matchJoinButton;
    Text* matchJoinText;

    CallbackParam<int> onJoinClicked;

    LobbyItemWidget(GUIManager& guiManager, int id, const string& ownerName, int playerCount,
                    int maxPlayersCount, CallbackParam<int> onJoin);

    ~LobbyItemWidget();

    void MoveContent(Vector2D movement);
};

#endif
