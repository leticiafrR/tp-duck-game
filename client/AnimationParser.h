#ifndef ANIMATION_PARSER_H
#define ANIMATION_PARSER_H

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include <SDL2pp/SDL2pp.hh>
#include <yaml-cpp/yaml.h>

using SDL2pp::Rect;

#define ANIM_PATH "../client/assets/animations/"

class AnimationParser {
private:
public:
    AnimationParser() = delete;
    ~AnimationParser() = delete;

    static std::map<std::string, std::vector<Rect>> ParseAnimationData(
            const std::string& filename) {
        YAML::Node yamlData = YAML::LoadFile(ANIM_PATH + filename);

        std::map<std::string, std::vector<Rect>> data;

        for (const auto& item: yamlData) {
            const std::string animKey = item.first.as<std::string>();

            std::vector<Rect> rects;
            std::transform(item.second.begin(), item.second.end(), std::back_inserter(rects),
                           [](const YAML::Node& rectItem) {
                               return Rect(rectItem["x"].as<int>(), rectItem["y"].as<int>(),
                                           rectItem["w"].as<int>(), rectItem["h"].as<int>());
                           });

            data[animKey] = rects;
        }
        return data;
    }
};

#endif
