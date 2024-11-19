#ifndef CLIENT_RUNNER_H
#define CLIENT_RUNNER_H

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "network/Client.h"

#include "AudioManager.h"
#include "Camera.h"
#include "Gameplay.h"
#include "LoadingScreen.h"
#include "LobbyScreen.h"
#include "MatchListScreen.h"
#include "MenuScreen.h"
#include "Rate.h"

using std::shared_ptr;
using std::string;
using std::vector;

class ClientRunner {
private:
    Camera cam;
    Rate rate;

    void ShowWinner(Client& client, vector<PlayerData> players) {
        PlayerID_t winnerId;
        LoadingScreen(cam, rate, [&client, &winnerId]() {
            shared_ptr<FinalWinner> msg;

            if (client.TryRecvNetworkMsg(msg)) {
                winnerId = msg->winner;
                return true;
            }
            return false;
        }).Run("GETTING WINNER...");

        auto it = std::find_if(players.begin(), players.end(),
                               [&winnerId](PlayerData p) { return p.playerID == winnerId; });

        LoadingScreen(cam, rate, [&client, &winnerId]() {
            return false;
        }).Run(it != players.end() ? "The winner is: " + it->nickname : "There is no winner");
    }

    void LoadFinalGroup(Client& client, bool& isFinalGroup) {
        LoadingScreen loadingFinalGroup(cam, rate, [&isFinalGroup, &client]() {
            shared_ptr<FinalGroupGame> finalGroupData;

            if (client.TryRecvNetworkMsg(finalGroupData)) {
                isFinalGroup = finalGroupData->finalGroupGame;
                return true;
            }
            return false;
        });
        loadingFinalGroup.Run("LOADING...");
    }

    void LoadMatchEnded(Client& client, bool& matchEnded) {
        LoadingScreen matchEndedScreen(cam, rate, [&client, &matchEnded]() {
            shared_ptr<GamesRecountDto> recountData;
            if (client.TryRecvNetworkMsg(recountData)) {
                matchEnded = recountData->matchEnded;
                return true;
            }
            return false;
        });
        matchEndedScreen.Run("GETTING RESULTS");
    }

    void PlayRound(Client& client, MatchStartDto matchData) {
        shared_ptr<GameSceneDto> mapData = nullptr;
        shared_ptr<Snapshot> firstSnapshot = nullptr;

        LoadingScreen laodRoundScreen(cam, rate, [&client, &mapData, &firstSnapshot]() {
            if (!mapData)
                client.TryRecvNetworkMsg(mapData);
            if (mapData && !firstSnapshot)
                client.TryRecvNetworkMsg(firstSnapshot);
            return mapData && firstSnapshot;
        });

        laodRoundScreen.Run("LOADING...");
        Gameplay(client, cam, rate, matchData, *mapData, *firstSnapshot).Run();
    }

    void ErrorScreen(const string& text) {
        LoadingScreen(cam, rate, []() { return false; }).Run(text);
    }

public:
    ClientRunner(Renderer& render, int fps): cam(std::move(render), 70), rate(fps) {}
    ~ClientRunner() = default;

    void Run() {
        try {
            string nickname = MenuScreen(cam, rate).Render();

            Client client("8080", "localhost", nickname);
            bool isOwner = MatchListScreen(cam, rate, client).Render();

            MatchStartDto matchData = *(LobbyScreen(cam, rate, client, isOwner).Render());

            bool matchEnded = false;

            while (!matchEnded) {
                PlayRound(client, matchData);

                bool isFinalGroup = false;
                while (!isFinalGroup) {
                    PlayRound(client, matchData);
                    LoadFinalGroup(client, isFinalGroup);
                }

                LoadMatchEnded(client, matchEnded);
            }
            ShowWinner(client, matchData.playersData);

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
