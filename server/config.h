#ifndef CONFIG_H_
#define CONFIG_H_

#include <iostream>
#include <string>
#include <vector>

#include "common/Vector2D.h"

// would be readed form a file .yaml
#define MAX_PLAYERS 5
#define MIN_PLAYERS 2
#define GAMES_TO_WIN_MATCH 10
#define GAMES_IN_GROUP 5


class Config {

    /* A vector that must be initialized with the name of the files yaml in the directory
     * server/maps. Those files must have the following content: The name of theme of that level
     * (descibe the background maybe the tiles) and then a descripction that allow a parser to read
     * where are the platafforms in the world of 100x100 */

    /* For the dummy Match we are going to hardcode some fake names*/
    const std::vector<std::string> _availableLevels;

    /* its a number with the quantity of different skins availables (for the clients), probably must
     * be read from a file .yaml with the settings*/
    const int _maxPlayers;
    const int _minPlayers;
    const int _gamesToWinMatch;
    const int _gamesInGroup;


public:
    Config():
            _availableLevels({"level_1.yaml"}),
            _maxPlayers(MAX_PLAYERS),
            _minPlayers(MIN_PLAYERS),
            _gamesToWinMatch(GAMES_TO_WIN_MATCH),
            _gamesInGroup(GAMES_IN_GROUP) {}

    const std::vector<std::string> getAvailableLevels() const { return _availableLevels; }
    int getAvailableSkins() const { return _maxPlayers; }
    int getMaxPlayers() const { return _maxPlayers; }
    int getMinPlayers() const { return _minPlayers; }
    int gamesToWinMatch() const { return _gamesToWinMatch; }
    int gamesInGroup() const { return _gamesInGroup; }
};

#endif
