#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "constants.h"
#include "constantsEditor.h"

void AddNewLevelToTheList(const std::string& filePath) {
    YAML::Node config = YAML::LoadFile(AVAILABLE_LEVELS_PATH);
    std::vector<std::string> _availableLevels =
            config[AVAILABLE_LEVELS_STR].as<std::vector<std::string>>();
    _availableLevels.emplace_back(filePath);
    config[AVAILABLE_LEVELS_STR] = _availableLevels;

    std::ofstream fout(AVAILABLE_LEVELS_PATH);
    fout << config;
}

int main() {
    YAML::Node config;
    YAML::Node playersSpawnPoints = YAML::Node(YAML::NodeType::Sequence);
    // Adding player spawn points
    int x = -18;
    int y = 12;
    playersSpawnPoints.push_back(YAML::Node(YAML::NodeType::Map));
    playersSpawnPoints[0]["x"] = x;
    playersSpawnPoints[0]["y"] = y;
    x = 32;
    y = -8;
    playersSpawnPoints.push_back(YAML::Node(YAML::NodeType::Map));
    playersSpawnPoints[1]["x"] = x;
    playersSpawnPoints[1]["y"] = y;  // Adding the nodes to the config
    config["players_spawn_points"] = playersSpawnPoints;

    std::cout << "" << std::endl;
    std::string fileName;
    std::cin >> fileName;
    std::string path = RELATIVE_LEVEL_PATH + fileName + YAML_FILE;

    std::ofstream fout(path);
    fout << config;

    return 0;
}
