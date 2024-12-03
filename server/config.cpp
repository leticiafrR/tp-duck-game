#include "config.h"

#include "../constants.h"

#include "constantServer.h"

Config::Config() {
    setAvaiableLevels();
    setMatchConfig();
    setWeaponsConfig();
    setDuckConfig();
    setObjectConfig();
}

void Config::setShotConfig(const YAML::Node& config) {
    inclinations.emplace_back(config[SHO0TING_INCLINATION_STR][BASIC_STR].as<float>());
    inclinations.emplace_back(config[SHO0TING_INCLINATION_STR][LASER_RIFLE_STR].as<float>());

    projectilesPerShot.emplace_back(config[PROJECTILE_PER_SHOT_STR][BASIC_STR].as<uint8_t>());
    projectilesPerShot.emplace_back(config[PROJECTILE_PER_SHOT_STR][BOX_STR].as<uint8_t>());
    projectilesPerShot.emplace_back(config[PROJECTILE_PER_SHOT_STR][GRANADE_STR].as<uint8_t>());
}

void Config::setAvaiableLevels() {
    YAML::Node config = YAML::LoadFile(AVAILABLE_LEVELS_PATH);
    _availableLevels = config[AVAILABLE_LEVELS_STR].as<std::vector<std::string>>();
}

void Config::setMatchConfig() {
    YAML::Node config = YAML::LoadFile(MATCH_PATH);
    try {
        _maxPlayers = config[MAX_PLAYERS_STR].as<int>();
        _minPlayers = config[MIN_PLAYERS_STR].as<int>();
        _gamesToWinMatch = config[MAX_PLAYERS_STR].as<int>();
        _gamesInGroup = config[MAX_PLAYERS_STR].as<int>();
    } catch (const YAML::TypedBadConversion<int>& e) {
        std::cerr << "[CONFIG]: Error converting YAML node to int for match: "
                  << " - " << e.what() << std::endl;
    } catch (const YAML::Exception& e) {
        std::cerr << "[CONFIG]: YAML exception for match: "
                  << " - " << e.what() << std::endl;
    }
}

void Config::setDuckConfig() {
    YAML::Node config = YAML::LoadFile(DUCK_PATH);
    duck.emplace_back(config[SIZE_STR].as<int>());
    duck.emplace_back(config[LIFE_STR].as<int>());
    duck.emplace_back(config[SPEED_STR].as<int>());
    duck.emplace_back(config[MASS_STR].as<int>());
}

void Config::setObjectConfig() {
    YAML::Node config = YAML::LoadFile(OBJECT_PATH);
    boxInfo.emplace_back(config[BOX_STR][SIZE_STR].as<int>());
    boxInfo.emplace_back(config[BOX_STR][LIFE_STR].as<int>());
    collectableInfo.emplace_back(config[COLLECTABLE_STR][SIZE_STR].as<int>());
}

void Config::setAWeapon(const std::string& name, const YAML::Node& config) {

    std::vector<uint8_t> weapon;
    weapon.emplace_back(config[name][AMMO_STR].as<uint8_t>());
    weapon.emplace_back(config[name][SCOPE_STR].as<uint8_t>());
    weapons.emplace_back(weapon);
}

void Config::setDispersion(const YAML::Node& config) {
    dispersions.emplace_back(config[NO_DISPERSION_STR].as<float>());
    dispersions.emplace_back(config[SHORT_STR].as<float>());
    dispersions.emplace_back(config[LONG_STR].as<float>());
    dispersions.emplace_back(config[SUPER_DISPERSION].as<float>());
    dispersions.emplace_back(config[HIPER_DISPERSION].as<float>());
}

void Config::setWeaponsConfig() {
    YAML::Node config = YAML::LoadFile(WEAPONS_PATH);
    setShotConfig(config);
    setDispersion(config[DISPERSION_STR]);
    setCooldown(config[COOLDOWN_STR]);
    setDamage(config[DAMAGE_STR]);
    setAWeapon(BANANA_STR, config);
    setAWeapon(LASER_RIFLE_STR, config);
    setAWeapon(GRANADE_STR, config);
    setAWeapon(COWBOY_PISTOL_STR, config);
    setAWeapon(AK47_STR, config);
    setAWeapon(DUELING_PISTOL_STR, config);
    setAWeapon(MANGUM_STR, config);
    setAWeapon(SHOTGUN_STR, config);
    setAWeapon(SNIPER_STR, config);
    setAWeapon(PEW_PEW_LASER_STR, config);
}

void Config::setCooldown(const YAML::Node& config) {
    cooldown.emplace_back(config[NONE_STR].as<float>());
    cooldown.emplace_back(config[SHORT_STR].as<float>());
    cooldown.emplace_back(config[LONG_STR].as<float>());
    cooldown.emplace_back(config[MEDIUM_STR].as<float>());
    cooldown.emplace_back(config[BASIC_STR].as<float>());
    cooldown.emplace_back(config[TO_EXPLOTE_GRANADE_STR].as<float>());
}

void Config::setDamage(const YAML::Node& config) {
    damage.emplace_back(config[MINIMUN_STR].as<int>());
    damage.emplace_back(config[SHORT_STR].as<int>());
    damage.emplace_back(config[MEDIUM_STR].as<int>());
    damage.emplace_back(config[LONG_STR].as<int>());
}


/**************************GETTERS****************************************/
const std::vector<std::string> Config::getAvailableLevels() const { return _availableLevels; }
int Config::getDuckMass() const { return duck[MASS_INDEX]; }
int Config::getDuckSize() const { return duck[SIZE_INDEX]; }
int Config::getDuckLife() const { return duck[LIFE_INDEX]; }
int Config::getDuckSpeed() const { return duck[SPEED_INDEX]; }
int Config::getAvailableSkins() const { return _maxPlayers; }
int Config::getMaxPlayers() const { return _maxPlayers; }
int Config::getMinPlayers() const { return _minPlayers; }
int Config::gamesToWinMatch() const { return _gamesToWinMatch; }
int Config::gamesInGroup() const { return _gamesInGroup; }
uint16_t Config::getBananaAmmo() const { return (uint16_t)weapons[BANANA_INDEX][AMMO_INDEX]; }
int Config::getBananaScope() const { return (int)weapons[BANANA_INDEX][SCOPE_INDEX]; }
uint16_t Config::getLaserRifleAmmo() const { return (int)weapons[LASER_RIFLE_INDEX][AMMO_INDEX]; }
int Config::getLaserRifleScope() const { return (int)weapons[LASER_RIFLE_INDEX][SCOPE_INDEX]; }
uint16_t Config::getCowboyPistolAmmo() const {
    return (uint16_t)weapons[COWBOY_PISTOL_INDEX][AMMO_INDEX];
}
int Config::getCowboyPistolScope() const { return (int)weapons[COWBOY_PISTOL_INDEX][SCOPE_INDEX]; }
uint16_t Config::getGranadaAmmo() const { return (uint16_t)weapons[GRANADE_INDEX][AMMO_INDEX]; }
int Config::getGranadaScope() const { return (int)weapons[GRANADE_INDEX][SCOPE_INDEX]; }
uint16_t Config::getAK47Ammo() const { return (uint16_t)weapons[AK47_INDEX][SCOPE_INDEX]; }
int Config::getAK47Scope() const { return (int)weapons[AK47_INDEX][AMMO_INDEX]; }
uint16_t Config::getDuelingPistolAmmo() const {
    return (uint16_t)weapons[DUELING_PISTOL_INDEX][AMMO_INDEX];
}
int Config::getDuelingPistolScope() const {
    return (int)weapons[DUELING_PISTOL_INDEX][SCOPE_INDEX];
}
uint16_t Config::getMagnumAmmo() const { return (uint16_t)weapons[MAGNUM_INDEX][AMMO_INDEX]; }
int Config::getMagnumScope() const { return (int)weapons[MAGNUM_INDEX][SCOPE_INDEX]; }
uint16_t Config::getShotgunAmmo() const { return (uint16_t)weapons[SHOTGUN_INDEX][AMMO_INDEX]; }
int Config::getShotgunScope() const { return (int)weapons[SHOTGUN_INDEX][SCOPE_INDEX]; }
uint16_t Config::getSniperAmmo() const { return (uint16_t)weapons[SNIPER_INDEX][AMMO_INDEX]; }
int Config::getSniperScope() const { return (int)weapons[SNIPER_INDEX][SCOPE_INDEX]; }
uint16_t Config::getPewPewLaserAmmo() const {
    return (uint16_t)weapons[PEW_PEW_LASER_INDEX][AMMO_INDEX];
}
int Config::getPewPewLaserScope() const { return (int)weapons[PEW_PEW_LASER_INDEX][SCOPE_INDEX]; }
// Dispersion
float Config::getNoDispersion() const { return dispersions[NONE_INDEX]; }
float Config::getShortDispersion() const { return dispersions[SHORT_INDEX]; }
float Config::getLongDispersion() const { return dispersions[LONG_INDEX]; }
float Config::getSuperDispersion() const { return dispersions[SUPER_INDEX]; }
float Config::getHiperDispersion() const { return dispersions[HIPER_INDEX]; }
// Cooldown
float Config::getCooldownNone() const { return cooldown[NONE_INDEX]; }
float Config::getCooldownShort() const { return cooldown[SHORT_INDEX]; }
float Config::getCooldownMedium() const { return cooldown[MEDIUM_INDEX]; }
float Config::getCooldownLong() const { return cooldown[LONG_INDEX]; }
float Config::getTimeToExploteGranade() const { return cooldown[TO_EXPLOTE_GRANADA_INDEX]; }
float Config::getCooldownBasic() const { return cooldown[BASIC_INDEX]; }
// Damage
int Config::getDamageMinimun() const { return damage[MINIMUN_INDEX]; }
int Config::getDamageShort() const { return damage[SHORT_INDEX]; }
int Config::getDamageMedium() const { return damage[MEDIUM_INDEX]; }
int Config::getDamageLong() const { return damage[LONG_INDEX]; }

/*********************SHOTING INCILNATION**************************** */
float Config::getBasicInclination() const { return inclinations[NONE_INDEX]; }
float Config::getLaserRifleInclination() const { return inclinations[LASER_RIFLE_INDEX]; }

/********************PROJECTILES PER SHOT**************************** */
uint8_t Config::getProjectilePerShotBasic() const { return projectilesPerShot[NONE_INDEX]; }
uint8_t Config::getFragmentGranade() const { return projectilesPerShot[GRANADE_INDEX]; }
uint8_t Config::getFragmentBox() const { return projectilesPerShot[BOX_INDEX]; }

int Config::getObjectSize() const { return collectableInfo[SIZE_INDEX]; }
int Config::getBoxSize() const { return boxInfo[SIZE_INDEX]; }
int Config::getBoxLife() const { return boxInfo[LIFE_INDEX]; }
