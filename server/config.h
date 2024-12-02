#ifndef CONFIG_H_
#define CONFIG_H_

#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "common/Vector2D.h"

enum class TypeItem : uint8_t;
enum class TypeProjectile : uint8_t;
class Config {
    std::vector<std::string> _availableLevels;
    int _maxPlayers;
    int _minPlayers;
    int _gamesToWinMatch;
    int _gamesInGroup;
    std::vector<int> duck;
    std::vector<std::vector<uint8_t>> weapons;
    std::vector<float> cooldown;
    std::vector<int> damage;
    std::vector<float> dispersions;
    std::vector<float> inclinations;
    std::vector<uint8_t> projectilesPerShot;

    void setAvaiableLevels();
    void setMatchConfig();
    void setDuckConfig();
    void setAWeapon(const std::string& name, const YAML::Node& con);
    void setWeaponsConfig();
    void setDispersion(const YAML::Node& config);
    void setCooldown(const YAML::Node& config);
    void setDamage(const YAML::Node& config);
    void setShotConfig(const YAML::Node& config);

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

    /***************************DAMAGE**************************************** */
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
    uint16_t getAK47Ammo() const;
    uint16_t getDuelingPistolAmmo() const;
    uint16_t getMagnumAmmo() const;
    uint16_t getShotgunAmmo() const;
    uint16_t getSniperAmmo() const;
    uint16_t getPewPewLaserAmmo() const;
    /****************************SCOPE********************************** */
    int getLaserRifleScope() const;
    int getBananaScope() const;
    int getCowboyPistolScope() const;
    int getGranadaScope() const;
    int getAK47Scope() const;
    int getDuelingPistolScope() const;
    int getMagnumScope() const;
    int getShotgunScope() const;
    int getSniperScope() const;
    int getPewPewLaserScope() const;
    /***********************DISPERSION********************************** */
    float getNoDispersion() const;
    float getShortDispersion() const;
    float getLongDispersion() const;
    float getSuperDispersion() const;
    float getHiperDispersion() const;

    /*********************SHOTING INCILNATION**************************** */
    float getBasicInclination() const;
    float getLaserRifleInclination() const;

    /********************PROJECTILES PER SHOT**************************** */
    uint8_t getProjectilePerShotBasic() const;
};
#endif
