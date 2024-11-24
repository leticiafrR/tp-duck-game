#include "mapEditor.h"
MapEditor::MapEditor(): config(), plataformsCounter(0) {}

MapEditor::MapEditor(const std::string& filePath): config(filePath), plataformsCounter(0) {}
void MapEditor::SaveChanges() {
    std::string filePath = RELATIVE_LEVEL_PATH + fileName + YAML_FILE;

    std::ofstream fout(filePath);
    fout << config;

    YAML::Node availableConfig = YAML::LoadFile(AVAILABLE_LEVELS_PATH);
    std::vector<std::string> availableLevels =
            availableConfig[AVAILABLE_LEVELS_STR].as<std::vector<std::string>>();

    auto it = std::find(availableLevels.begin(), availableLevels.end(), filePath);
    if (it == availableLevels.end()) {
        availableLevels.emplace_back(filePath);
        availableConfig[AVAILABLE_LEVELS_STR] = availableLevels;
        std::ofstream fout2(AVAILABLE_LEVELS_PATH);
        fout2 << availableConfig;
    }
}

void MapEditor::AddFileName(const std::string& _fileName) { fileName = _fileName; }
