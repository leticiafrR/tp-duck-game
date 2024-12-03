
#ifndef CLIENT_RUNNER_H
#define CLIENT_RUNNER_H

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "game/GameScreen.h"
#include "menus/Menus.h"
#include "network/Client.h"

#include "Framework.h"

using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::vector;

class ClientRunner {
private:
    Camera cam;
    ResourceManager resource;
    bool wasClosed;

    void LoadWinner(Client& client, vector<PlayerData> players, std::optional<PlayerData>& winner);

    void LoadFinalGroup(Client& client, bool& isFinalGroup);

    void LoadRoundResults(Client& client, bool& matchEnded,
                          unordered_map<PlayerID_t, int>& results);

    void PlayRound(Client& client, MatchStartDto matchData, bool isInitial);

    void ErrorScreen(const string& text);

    void ShowResultsScreen(std::optional<PlayerData> winner, const vector<PlayerData>& players,
                           const unordered_map<PlayerID_t, int>& gameResults);

    void KillClient(Client& client);


    void PlayConnected(Client& client);

public:
    ClientRunner(Renderer& render, int fps);
    ~ClientRunner();

    void Run();
};

#endif
