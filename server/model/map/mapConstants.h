#ifndef MAPCONSTANTS_H
#define MAPCONSTANTS_H
#include <cstdint>
#include <set>
#include <string>
#include <vector>

#include "data/gameScene.h"

// typedef enum: uint8_t { LEFT, RIGHT, TOP, BOTTOM } VISIBLE_EDGES;
/*  Esta informacion se encuentrara en un archivo .YAML y contempla los objetos estaticos participes
 *   del escenario, el tamanio del mundo, ubicacion y tamanio de las plataformas y paredes en la
 * misma. Cada plataforma o pared posee la posicion en su centro y su tamanio.
 */
namespace Theme {
const std::string Forest = "FOREST";
}
namespace FullMapSize {
const size_t xMapSize = 100;
const size_t yMapSize = 160;
}  // namespace FullMapSize

const float distanceBetweenTwoBlocks = 0;

namespace PlayersSpawnPlaceEasyLevel {
std::vector<Vector2D> points{Vector2D(-18, 12), Vector2D(32 + distanceBetweenTwoBlocks, -8)};
}

namespace PlataformOne {
const float xPos = 0;
const float yPos = -12;
const float xSize = 24;
const float ySize = 8;
std::set<VISIBLE_EDGES> edges = {RIGHT, TOP, BOTTOM};
}  // namespace PlataformOne

namespace PlataformTwo {
const float xPos = -32;
const float yPos = 0;
const float xSize = 40;
const float ySize = 16;
std::set<VISIBLE_EDGES> edges = {LEFT, RIGHT, TOP};
}  // namespace PlataformTwo

namespace PlataformThree {
const float xPos = -32;
const float yPos = -12;
const float xSize = 40;
const float ySize = 8;
std::set<VISIBLE_EDGES> edges = {LEFT, BOTTOM};
}  // namespace PlataformThree

namespace PlataformFour {
const float xPos = 20 + distanceBetweenTwoBlocks;
const float yPos = -8;
const float xSize = 16;
const float ySize = 8;
std::set<VISIBLE_EDGES> edges = {LEFT, RIGHT, TOP};
}  // namespace PlataformFour

namespace PlataformFive {
const float xPos = 20 + distanceBetweenTwoBlocks;
const float yPos = -20;
const float xSize = 16;
const float ySize = 16;
std::set<VISIBLE_EDGES> edges = {LEFT, BOTTOM};
}  // namespace PlataformFive

namespace PlataformSix {
const float xPos = 32 + distanceBetweenTwoBlocks;
const float yPos = -20;
const float xSize = 8;
const float ySize = 16;
std::set<VISIBLE_EDGES> edges = {TOP, BOTTOM};
}  // namespace PlataformSix

namespace PlataformSeven {
const float xPos = 40 + distanceBetweenTwoBlocks;
const float yPos = -20;
const float xSize = 8;
const float ySize = 16;
std::set<VISIBLE_EDGES> edges = {RIGHT, BOTTOM};
}  // namespace PlataformSeven

namespace PlataformEight {
const float xPos = 40 + distanceBetweenTwoBlocks;
const float yPos = -4;
const float xSize = 8;
const float ySize = 16;
std::set<VISIBLE_EDGES> edges = {RIGHT, LEFT, TOP};
}  // namespace PlataformEight

#endif
