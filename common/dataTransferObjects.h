#ifndef DTO_H
#define DTO_H

#include <string>
#include <unordered_map>
#include <vector>

#include "../common/Transform.h"
#include "../common/Vector2D.h"
#include "../data/id.h"

// creo que estos objetos no deberìan de recibir referenciaas a algo porque sino lo que se pase al
// protocolo se contarìa como un recurso compartido
// de igual forma se deberìa copiar todo al pushear a las diferentes colas

struct MatchStartSettingsDto {
    std::vector<PlayerID_t> playerIDs;
    std::vector<std::string> playerNicknames;
    std::vector<int> playerSkins;
    Vector2D duckSize;  // igual el protocolo enviarìa esto como enteros creo.

    MatchStartSettingsDto(int numberPlayers, Vector2D duckSize):
            playerIDs(numberPlayers),
            playerNicknames(numberPlayers),
            playerSkins(numberPlayers),
            duckSize(duckSize) {}
};

// no comunicar el valor de los angulos
struct GameStartSettingsDto {
    std::string theme;
    std::vector<Transform> platforms;
    // cppcheck-suppress passedByValue
    GameStartSettingsDto(std::string theme, std::vector<Transform> platforms):
            theme(theme), platforms(platforms) {}
};

struct Snapshot {
    bool gameEnded;
    std::unordered_map<PlayerID_t, Vector2D> positionsUpdate;

    // cppcheck-suppress passedByValue
    Snapshot(bool gameEnded, std::unordered_map<PlayerID_t, Vector2D> positionsUpdate):
            gameEnded(gameEnded), positionsUpdate(positionsUpdate) {}
};

struct GamesRecountDto {
    bool matchEnded;
    std::unordered_map<PlayerID_t, int> results;
    // cppcheck-suppress passedByValue
    GamesRecountDto(bool matchEnded, std::unordered_map<PlayerID_t, int> results):
            matchEnded(matchEnded), results(results) {}
};


#endif
