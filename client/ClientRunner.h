
#ifndef CLIENT_RUNNER_H
#define CLIENT_RUNNER_H

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "gameplay/Gameplay.h"
#include "multimedia/AudioManager.h"
#include "multimedia/Camera.h"
#include "network/Client.h"
#include "screens/GameStatusScreen.h"
#include "screens/LoadingScreen.h"
#include "screens/LobbyScreen.h"
#include "screens/MatchListScreen.h"
#include "screens/MenuScreen.h"

using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::vector;

class ClientRunner {
private:
    Camera cam;

    PlayerData LoadWinner(Client& client, vector<PlayerData> players) {
        PlayerID_t winnerId;
        LoadingScreen(cam, [&client, &winnerId]() {
            shared_ptr<FinalWinner> msg;

            if (client.TryRecvNetworkMsg(msg)) {
                winnerId = msg->winner;
                return true;
            }
            return false;
        }).Run("GETTING WINNER...");
        auto it = std::find_if(players.begin(), players.end(),
                               [&winnerId](PlayerData p) { return p.playerID == winnerId; });
        return *it;
    }

    void LoadFinalGroup(Client& client, bool& isFinalGroup) {
        std::cout << "Waiting for final group"
                  << "\n";
        LoadingScreen loadingFinalGroup(cam, [&isFinalGroup, &client]() {
            shared_ptr<FinalGroupGame> finalGroupData;

            if (client.TryRecvNetworkMsg(finalGroupData)) {
                isFinalGroup = finalGroupData->finalGroupGame;
                std::cout << "Received final group"
                          << "\n";
                return true;
            }
            return false;
        });
        loadingFinalGroup.Run("LOADING...");
    }

    void LoadRoundResults(Client& client, bool& matchEnded,
                          unordered_map<PlayerID_t, int>& results) {
        LoadingScreen matchEndedScreen(cam, [&client, &matchEnded, &results]() {
            shared_ptr<GamesRecountDto> recountData;
            if (client.TryRecvNetworkMsg(recountData)) {
                matchEnded = recountData->matchEnded;
                results = recountData->results;
                return true;
            }
            return false;
        });
        matchEndedScreen.Run("GETTING RESULTS");
    }

    void PlayRound(Client& client, MatchStartDto matchData, bool isInitial) {
        shared_ptr<GameSceneDto> mapData = nullptr;
        shared_ptr<Snapshot> firstSnapshot = nullptr;

        LoadingScreen laodRoundScreen(cam, [&client, &mapData, &firstSnapshot]() {
            if (!mapData)
                client.TryRecvNetworkMsg(mapData);
            if (mapData && !firstSnapshot)
                client.TryRecvNetworkMsg(firstSnapshot);
            return mapData && firstSnapshot;
        });

        laodRoundScreen.Run("LOADING...");
        Gameplay(client, cam, matchData, *mapData, *firstSnapshot).Run(isInitial);
    }

    void ErrorScreen(const string& text) {
        LoadingScreen(cam, []() { return false; }).Run(text);
    }

    void ShowResultsScreen(std::optional<PlayerData> winner, const vector<PlayerData>& players,
                           const unordered_map<PlayerID_t, int>& gameResults) {

        GameStatusScreen(cam, players, gameResults, winner).Run();
    }

public:
    ClientRunner(Renderer& render, int fps): cam(std::move(render), 70, Rate(fps)) {}
    ~ClientRunner() = default;

    void Run() {
        try {
            string nickname = MenuScreen(cam).Render();

            Client client("8080", "localhost", nickname);
            bool isOwner = MatchListScreen(cam, client).Render();

            MatchStartDto matchData = *(LobbyScreen(cam, client, isOwner).Render());

            AudioManager::GetInstance().PlayGameMusic();
            bool matchEnded = false;
            unordered_map<PlayerID_t, int> roundResults;
            bool isInitial = true;
            while (!matchEnded) {
                PlayRound(client, matchData, isInitial);
                isInitial = false;

                bool isFinalGroup = false;
                LoadFinalGroup(client, isFinalGroup);

                while (!isFinalGroup) {
                    PlayRound(client, matchData, isInitial);
                    LoadFinalGroup(client, isFinalGroup);
                }

                LoadRoundResults(client, matchEnded, roundResults);

                if (!matchEnded) {
                    ShowResultsScreen(std::nullopt, matchData.playersData, roundResults);
                }
            }
            AudioManager::GetInstance().StopMusic();

            PlayerData winner = LoadWinner(client, matchData.playersData);

            ShowResultsScreen(winner, matchData.playersData, roundResults);

        } catch (LibError& e) {
            std::cerr << e.what() << std::endl;
            ErrorScreen("Can't connect to server, please try again later");

        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            ErrorScreen("An unexpected error occurred, please try again later");
        }
    }
};

#endif
