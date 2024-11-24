#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "constants.h"
#include "constantsEditor.h"

// Se encarga de crear o guardar los cambios y settear el nombre del nivel en la lista
void SaveChanges(const std::string& fileName, const YAML::Node& config) {
    std::string filePath = RELATIVE_LEVEL_PATH + fileName + YAML_FILE;

    // Guardar el archivo de configuración
    {
        std::ofstream fout(filePath);
        fout << config;
    }

    // Cargar niveles disponibles
    YAML::Node availableConfig = YAML::LoadFile(AVAILABLE_LEVELS_PATH);
    std::vector<std::string> availableLevels =
            availableConfig[AVAILABLE_LEVELS_STR].as<std::vector<std::string>>();

    // Verificar si el archivo ya existe en la lista de niveles disponibles
    auto it = std::find(availableLevels.begin(), availableLevels.end(), filePath);
    if (it == availableLevels.end()) {
        availableLevels.emplace_back(filePath);
        availableConfig[AVAILABLE_LEVELS_STR] = availableLevels;

        // Guardar los cambios en la lista de niveles disponibles
        std::ofstream fout(AVAILABLE_LEVELS_PATH);
        fout << availableConfig;
    }
}

int main() {
    YAML::Node config;
    YAML::Node playersSpawnPoints = YAML::Node(YAML::NodeType::Sequence);

    // Agregar puntos de aparición de jugadores
    int x = -18;
    int y = 12;
    playersSpawnPoints.push_back(YAML::Node(YAML::NodeType::Map));
    playersSpawnPoints[0]["x"] = x;
    playersSpawnPoints[0]["y"] = y;

    x = 32;
    y = -8;
    playersSpawnPoints.push_back(YAML::Node(YAML::NodeType::Map));
    playersSpawnPoints[1]["x"] = x;
    playersSpawnPoints[1]["y"] = y;

    // Agregar los nodos a la configuración
    config["players_spawn_points"] = playersSpawnPoints;

    // Guardar cambios
    SaveChanges("config.yaml", config);

    return 0;
}
