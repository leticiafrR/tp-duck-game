#include "LobbyItemWidget.h"

LobbyItemWidget::LobbyItemWidget(GUIManager& guiManager, int id, const string& ownerName,
                                 int playerCount, int maxPlayersCount, CallbackParam<int> onJoin):
        lobbyId(id), onJoinClicked(onJoin) {

    matchConentImage = guiManager.CreateImage(
            RectTransform(Vector2D(0, 0), Vector2D(900, 120), Vector2D(0.5, 1)), 0,
            Color(160, 160, 160));

    matchOwnerText = guiManager.CreateText(
            RectTransform(Vector2D(-280, 0), Vector2D(300, 120), Vector2D(0.5, 1)), 1,
            ownerName + " lobby", 30);

    matchPlayersText = guiManager.CreateText(
            RectTransform(Vector2D(0, 0), Vector2D(180, 120), Vector2D(0.5, 1)), 1,
            "Players" + std::to_string(playerCount) + "/" + std::to_string(maxPlayersCount), 30);

    matchJoinButton = guiManager.CreateButton(
            RectTransform(Vector2D(280, 0), Vector2D(150, 80), Vector2D(0.5, 1)), 1,
            [this]() { this->onJoinClicked(this->lobbyId); });

    matchJoinText = guiManager.CreateText(
            RectTransform(Vector2D(280, 0), Vector2D(150, 80), Vector2D(0.5, 1)), 2, "Join", 30);
}

LobbyItemWidget::~LobbyItemWidget() = default;

void LobbyItemWidget::MoveContent(Vector2D movement) {
    matchConentImage->GetRectTransform().Move(movement);

    matchOwnerText->GetRectTransform().Move(movement);
    matchPlayersText->GetRectTransform().Move(movement);

    matchJoinButton->GetRectTransform().Move(movement);
    matchJoinText->GetRectTransform().Move(movement);
}
