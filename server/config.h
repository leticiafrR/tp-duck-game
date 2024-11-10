#ifndef CONFIG_H_
#define CONFIG_H_

#include <iostream>
#include <string>
#include <vector>

#include "common/Vector2D.h"

#define MAX_PLAYERS 5

class Config {

    /* A vector that must be initialized with the name of the files yaml in the directory
     * server/maps. Those files must have the following content: The name of theme of that level
     * (descibe the background maybe the tiles) and then a descripction that allow a parser to read
     * where are the platafforms in the world of 100x100 */

    /* For the dummy Match we are going to hardcode some fake names*/
    const std::vector<std::string> availableLevels;

    /* its a number with the quantity of different skins availables (for the clients), probably must
     * be read from a file .yaml with the settings*/
    const int maxPlayers;


public:
    Config(): availableLevels({"level_1.yaml"}), maxPlayers(MAX_PLAYERS) {

        /* for example for the correct initialization of the `availableLevels`.

        std::string mapsDir = "./maps";
        if (fs::exists(mapsDir) && fs::is_directory(mapsDir)) {
            for (const auto& entry : fs::directory_iterator(mapsDir)) {
                if (fs::is_regular_file(entry.path())) {
                    availableLevels.push_back(entry.path().filename().string());
                }
            }
        } else {
            std::cerr << "El directorio 'maps' no existe en el directorio actual." << std::endl;
        }
        */
    }

    const std::vector<std::string> getAvailableLevels() const { return availableLevels; }
    int getAvailableSkins() const { return maxPlayers; }
    int getMaxPlayers() const { return maxPlayers; }

    // Vector2D getDuckSize() {
    //     Vector2D duckSize(1.0, 1.0);
    //     return duckSize;
    // }
};

#endif
