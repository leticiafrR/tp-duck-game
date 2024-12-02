#include "ResourceParser.h"

MapThemeData ResourceParser::ParseMapThemeData(YAML::Node data) {
    MapThemeData mapThemeData;
    mapThemeData.bgfile = data["bg_file"].as<string>();
    mapThemeData.bgMusicFile = data["music_file"].as<string>();
    mapThemeData.tileSetFile = data["tile_set_file"].as<string>();

    for (const auto& frameItem: data["tile_rects"]) {
        const string key = frameItem.first.as<string>();

        vector<Rect> rects;
        std::transform(frameItem.second.begin(), frameItem.second.end(), std::back_inserter(rects),
                       [](const YAML::Node& rectItem) {
                           return Rect(rectItem["x"].as<int>(), rectItem["y"].as<int>(),
                                       rectItem["w"].as<int>(), rectItem["h"].as<int>());
                       });

        mapThemeData.tileRects[key] = rects;
    }

    return mapThemeData;
}

MenuData ResourceParser::ParseMenu(YAML::Node data) {
    MenuData menuData;
    menuData.menuBgFile = data["menu_bg"].as<string>();
    menuData.logoBgFile = data["logo_bg"].as<string>();
    menuData.buttonImgFile = data["button_img"].as<string>();
    menuData.buttonBackImgFile = data["button_back_img"].as<string>();
    menuData.buttonSfxFile = data["button_sfx"].as<string>();
    return menuData;
}

ArmorData ResourceParser::ParseArmor(YAML::Node data) {
    ArmorData armorData;
    armorData.file = data["file"].as<string>();

    for (const auto& frameItem: data["frames"]) {
        const string key = frameItem.first.as<string>();

        vector<Rect> rects;
        std::transform(frameItem.second.begin(), frameItem.second.end(), std::back_inserter(rects),
                       [](const YAML::Node& rectItem) {
                           return Rect(rectItem["x"].as<int>(), rectItem["y"].as<int>(),
                                       rectItem["w"].as<int>(), rectItem["h"].as<int>());
                       });

        armorData.frames[key] = rects;
    }

    return armorData;
}

DuckData ResourceParser::ParseDuck(YAML::Node data) {
    DuckData duckData;
    duckData.file = data["file"].as<string>();
    duckData.cuackFileSFX = data["cuack_sfx"].as<string>();
    duckData.damagedFileSFX = data["damaged_sfx"].as<string>();

    for (const auto& frameItem: data["frames"]) {
        const string key = frameItem.first.as<string>();

        vector<Rect> rects;
        std::transform(frameItem.second.begin(), frameItem.second.end(), std::back_inserter(rects),
                       [](const YAML::Node& rectItem) {
                           return Rect(rectItem["x"].as<int>(), rectItem["y"].as<int>(),
                                       rectItem["w"].as<int>(), rectItem["h"].as<int>());
                       });

        duckData.frames[key] = rects;
    }

    return duckData;
}

CollectableData ResourceParser::ParseCollectable(YAML::Node itemData) {
    CollectableData collectable;
    collectable.file = itemData["file"].as<string>();

    YAML::Node rectData = itemData["file_rect"];

    collectable.rect = Rect(rectData["x"].as<int>(), rectData["y"].as<int>(),
                            rectData["w"].as<int>(), rectData["h"].as<int>());

    YAML::Node sizeData = itemData["size"];
    collectable.size = Vector2D(sizeData["x"].as<float>(), sizeData["y"].as<float>());

    if (itemData["angle"].IsDefined()) {
        collectable.angle = itemData["angle"].as<float>();
    } else {
        collectable.angle = 0;
    }

    return collectable;
}

ProjectileData ResourceParser::ParseProjectil(YAML::Node itemData) {
    ProjectileData projectil;
    projectil.file = itemData["file"].as<string>();
    projectil.sfxFile = itemData["sfx_file"].as<string>();
    projectil.speed = itemData["visual_speed"].as<float>();

    YAML::Node rectData = itemData["file_rect"];

    projectil.rect = Rect(rectData["x"].as<int>(), rectData["y"].as<int>(), rectData["w"].as<int>(),
                          rectData["h"].as<int>());

    YAML::Node sizeData = itemData["size"];
    projectil.size = Vector2D(sizeData["x"].as<float>(), sizeData["y"].as<float>());

    return projectil;
}
