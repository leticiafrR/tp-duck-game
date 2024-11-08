#include <iostream>
#include <string>
#include <utility>

#include "common/socket.h"
#include "common/timeManager.h"

#include "clientProtocol.h"
#define QUIT "q"


void ShowIntialDta(const MatchStartDto& dta) {
    std::cout << "[INITIAL DATA]:\n";
    std::cout << "-> Duck size: (" << dta.duckSize.x << "," << dta.duckSize.y << ")\n";
    std::cout << "-> Players info:\n";
    for (PlayerData d: dta.playersData) {
        std::cout << "  -> ID:" << (int)d.playerID << "\n";
        std::cout << "  -> Skin:" << (int)d.playerSkin << "\n";
        std::cout << "  -> Name:" << d.nickname << "\n";
        std::cout << "\n";
    }
}

void ShowTransform(const Transform& t) {
    std::cout << "  -> size: (" << t.GetSize().x << "," << t.GetSize().y << ")\n";
    std::cout << "  -> pos: (" << t.GetPos().x << "," << t.GetPos().y << ")\n";
    std::cout << "  -> angle:" << t.GetAngle() << "\n";
    std::cout << "\n";
}

void ShowPlattaforms(const std::vector<Transform>& platforms) {
    int i = 0;
    for (auto& t: platforms) {
        std::cout << "  -> PLATTAFORM [" << i << "]\n";
        ShowTransform(t);
        i++;
    }
}


void ShowGroundBlocks(const std::vector<GroundDto>& blocks) {
    int i = 0;
    for (auto& b: blocks) {
        std::cout << "  -> GROUNDBLOCK [" << i << "]\n";
        // ShowVisibleEdges(b.visibleEdges);
        ShowTransform(b.transform);
        i++;
    }
}


void ShowGameSceneDta(const GameSceneDto& dta) {
    std::cout << "\n";
    std::cout << "[GameSceneDta] :\n";
    std::cout << "-> Theme: " << dta.theme << "\n";
    std::cout << "-> Plattaforms: "
              << "\n";
    ShowPlattaforms(dta.platforms);
    std::cout << "-> GroundBlocks: " << dta.theme << "\n";
    ShowGroundBlocks(dta.groundBlocks);
}
void ShowGameUpdate(const Snapshot& snapshot) {
    std::cout << "\n";
    std::cout << "\n[GameUpdate] :\n";
    std::cout << "-> gameOver: " << (snapshot.gameOver ? "true" : "false") << "\n";
    int i = 1;
    for (auto it = snapshot.updates.begin(); it != snapshot.updates.end(); it++) {
        std::cout << "->update " << i << " avo: "
                  << "\n   PlayerID:" << (int)it->first << "\n     POS:" << it->second.motion.x
                  << "," << it->second.motion.y << "\n";
        i++;
    }
}


int main(int argc, char* argv[]) {
    // Socket skt("127.0.0.1","8080");
    if (argc < 3) {
        std::cout << "Bad CAll\n";
        return -1;
    }
    Socket skt(argv[1], argv[2]);
    ClientProtocol protocol(std::move(skt));
    std::cout << "CONECTED TO THE SERVER!\n";
    std::cout << "Introduce your nickname\n";
    std::string in;
    std::cin >> in;

    std::string name = in;
    protocol.sendNickname(name);

    if (protocol.receiveStateOfJoining()) {

        std::cout << "We got accepted!\n";
        MatchStartDto startingDta = protocol.receiveMachStartDto();
        std::cout << "WE RECIEVED THE DETAILS OF THE MATCH:\n";
        ShowIntialDta(startingDta);


        std::cout << "\n\n ...Entering to the loop where we send commands and receive updates(dy "
                     "always to right, leti to left)...\n";
        TimeManager timeManager(1);
        // group of games
        while (true) {
            std::cout << "\n\n            STARTING A NEW GAME\n";
            GameSceneDto gameSceneDta = protocol.receiveGameSceneDto();
            std::cout << "We recieved the details of the game scene:\n";
            // ShowGameSceneDta(gameSceneDta);
            // game
            while (true) {
                std::cout << "\n -Recieving the snapshot:\n";
                Snapshot snapshot = protocol.receiveGameUpdateDto();
                ShowGameUpdate(snapshot);
                if (snapshot.gameOver) {
                    break;
                }
                if (name == "dy") {
                    std::cout << "\n -Sending the command to move rigth\n";
                    protocol.sendCommand(Command{CommandCode::MoveRight_KeyDown});

                } else if (name == "leti") {
                    std::cout << "\n -Sending the command to move left\n";
                    protocol.sendCommand(Command{CommandCode::MoveLeft_KeyDown});
                }
                timeManager.synchronizeTick();
            }
        }

    } else {
        std::cout << "Couldnt join the match!\n";
    }

    return 0;
}
