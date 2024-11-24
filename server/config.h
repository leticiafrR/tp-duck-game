#ifndef CONFIG_H_
#define CONFIG_H_

#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "common/Vector2D.h"

enum class TypeCollectable : uint8_t;
enum class TypeProjectile : uint8_t;
class Config {
    // cppcheck-suppress unusedStructMember
    std::vector<std::string> _availableLevels;
    // cppcheck-suppress unusedStructMember
    int _maxPlayers;
    // cppcheck-suppress unusedStructMember
    int _minPlayers;
    // cppcheck-suppress unusedStructMember
    int _gamesToWinMatch;
    // cppcheck-suppress unusedStructMember
    int _gamesInGroup;
    // cppcheck-suppress unusedStructMember
    std::vector<int> duck;
    // cppcheck-suppress unusedStructMember
    std::vector<std::vector<uint8_t>> weapons;
    // cppcheck-suppress unusedStructMember
    std::vector<float> cooldown;
    // cppcheck-suppress unusedStructMember
    std::vector<int> damage;
    // cppcheck-suppress unusedStructMember
    std::vector<float> dispersions;

    void setAvaiableLevels();
    void setMatchConfig();
    void setDuckConfig();
    void setAWeapon(const std::string& name, const YAML::Node& con);
    void setWeaponsConfig();
    void setDispersion(const YAML::Node& config);
    void setCooldown(const YAML::Node& config);
    void setDamage(const YAML::Node& config);

public:
    Config();
    /************************GAME****************************************** */
    const std::vector<std::string> getAvailableLevels() const;
    int getAvailableSkins() const;
    int getMaxPlayers() const;
    int getMinPlayers() const;
    int gamesToWinMatch() const;
    int gamesInGroup() const;

    /**************************COOLDOWN************************************* */
    float getCooldownNone() const;
    float getCooldownShort() const;
    float getCooldownBasic() const;
    float getCooldownMedium() const;
    float getCooldownLong() const;
    float getCooldownExploteGranada() const;


    int getDamageMinimun() const;
    int getDamageShort() const;
    int getDamageMedium() const;
    int getDamageLong() const;

    /***************************DUCK************************************** */
    int getDuckMass() const;
    int getDuckSize() const;
    int getDuckLife() const;
    int getDuckSpeed() const;
    /****************************AMMO*********************************** */
    uint16_t getLaserRifleAmmo() const;
    uint16_t getBananaAmmo() const;
    uint16_t getGranadaAmmo() const;
    uint16_t getCowboyPistolAmmo() const;
    /****************************SCOPE********************************** */
    int getLaserRifleScope() const;
    int getBananaScope() const;
    int getCowboyPistolScope() const;
    int getGranadaScope() const;
    /***********************DISPERSION********************************** */
    float getNoDispersion() const;
    float getShortDispersion() const;
    float getLongDispersion() const;

    // faltan implementar:
    int getAK47Ammo() const;
    int getAK47Scope() const;
    float getAK47Dispersion() const;

    int getDuelingPistolAmmo() const;
    int getDuelingPistolScope() const;
    float getDuelingPistolDispersion() const;

    int getMagnumAmmo() const;
    int getMAgnumScope() const;
    float getMagnumDispersion() const;

    int getShotgunAmmo() const;
    int getShotgunScope() const;
    float getShotgunDispersion() const;

    int getSniperAmmo() const;
    int getSniperScope() const;
    float getSniperDispersion() const;
};
#endif
