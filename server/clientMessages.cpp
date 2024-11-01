#include "clientMessages.h"

/********************** IMPLEMENTATION OF MATCH START SETTING MSSG ******************************/
MatchStartSettings::MatchStartSettings(SafeMap<PlayerID_t, PlayerInfo>& players, int numberSkins) {
    if (players.size() > numberSkins) {
        throw std::runtime_error(
                "ERROR: A unique assignment of skins to players cannot be made. Too many players");
    }
    // Generador de números aleatorios
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, numberSkins - 1);

    players.applyToItems([this, &gen, &dis](PlayerID_t playerID, PlayerInfo& playerInfo) {
        int skinIndx;
        do {
            skinIndx = dis(gen);
        } while (skinsAssignation.find(skinIndx) != skinsAssignation.end());
        skinsAssignation[skinIndx] = std::make_tuple(playerID, playerInfo.nickName);
    });
}

bool MatchStartSettings::sendMyself(ServerProtocol& protocol) {
    return protocol.sendMatchStartSettings(skinsAssignation);
}

/*********************** IMPLEMENTATION OF GAME START SETTINGS MSSG ***************************/
GameStartSettings::GameStartSettings(const std::string& theme,
                                     std::vector<Transform>&& gamePlatforms):
        theme(theme), gamePlatforms(std::move(gamePlatforms)) {}

bool GameStartSettings::sendMyself(ServerProtocol& protocol) {
    return protocol.sendGameStartSettings(theme, std::ref(gamePlatforms));
}

// /************************ IMPLEMENTATION OF GAMES RECOUNT MSSG *****************************/
// cppcheck-suppress passedByValue
GamesRecount::GamesRecount(std::unordered_map<PlayerID_t, int> results): results(results) {}

bool GamesRecount::sendMyself(ServerProtocol& protocol) {
    return protocol.sendGamesRecount(std::ref(results));
}

/************************ IMPLEMENTATION OF MATCH RESULT MSSG *****************************/
MatchResult::MatchResult(PlayerID_t finalWinner): finalWinner(finalWinner) {}

bool MatchResult::sendMyself(ServerProtocol& protocol) {
    return protocol.sendMatchResult(finalWinner);
}
