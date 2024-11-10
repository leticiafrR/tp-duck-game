#ifndef MAPCONSTANTS_H
#define MAPCONSTANTS_H
#include <cstdint>
#include <set>
#include <string>

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
const size_t yMapSize = 100;
}  // namespace FullMapSize

namespace TestLevel {
const float xPosition = 0;
const float yPosition = -1.5;
const float xLength = 60;
const float yLength = 3;
std::set<VISIBLE_EDGES> edges = {LEFT, RIGHT, TOP, BOTTOM};
}  // namespace TestLevel
namespace PlataformOne {
const float xPosition = -31;
const float yPosition = 28;
const float xLength = 17;
const float yLength = 9;
std::set<VISIBLE_EDGES> edges = {LEFT, RIGHT, TOP, BOTTOM};
}  // namespace PlataformOne

namespace PlataformTwo {
const float xPosition = 19;
const float yPosition = 14;
const float xLength = 25;
const float yLength = 9;
std::set<VISIBLE_EDGES> edges = {LEFT, RIGHT, TOP, BOTTOM};
}  // namespace PlataformTwo

namespace PlataformThree {
const float xPosition = 47.5;
const float yPosition = -16.5;
const float xLength = 5;
const float yLength = 17;
std::set<VISIBLE_EDGES> edges = {TOP};
}  // namespace PlataformThree

namespace PlataformFour {
const float xPosition = 47.5;
const float yPosition = -28;
const float xLength = 5;
const float yLength = 6;
}  // namespace PlataformFour

namespace PlataformFive {
const float xPosition = 33;
const float yPosition = -37.5;
const float xLength = 6;
const float yLength = 25;
std::set<VISIBLE_EDGES> edges = {LEFT, RIGHT, BOTTOM};
}  // namespace PlataformFive

namespace PlataformSix {
const float xPosition = 42.5;
const float yPosition = -16.5;
const float xLength = 5;
const float yLength = 17;
std::set<VISIBLE_EDGES> edges = {TOP};
}  // namespace PlataformSix

namespace PlataformSeven {
const float xPosition = 42.5;
const float yPosition = -28;
const float xLength = 5;
const float yLength = 6;
std::set<VISIBLE_EDGES> edges = {LEFT, TOP};
}  // namespace PlataformSeven

namespace PlataformEight {
const float xPosition = 38;
const float yPosition = -16.5;
const float xLength = 4;
const float yLength = 17;
std::set<VISIBLE_EDGES> edges = {BOTTOM, TOP};
}  // namespace PlataformEight

namespace PlataformNine {
const float xPosition = 33;
const float yPosition = -16.5;
const float xLength = 6;
const float yLength = 17;
std::set<VISIBLE_EDGES> edges = {LEFT, TOP};
}  // namespace PlataformNine

namespace PlataformTen {
const float xPosition = 13.5;
const float yPosition = -23;
const float xLength = 5;
const float yLength = 16;
std::set<VISIBLE_EDGES> edges = {RIGHT, TOP, BOTTOM};
}  // namespace PlataformTen

namespace PlataformEleven {
const float xPosition = 8.5;
const float yPosition = -23;
const float xLength = 5;
const float yLength = 16;
std::set<VISIBLE_EDGES> edges = {TOP};
}  // namespace PlataformEleven

namespace PlataformTwelve {
const float xPosition = 8.5;
const float yPosition = -34.5;
const float xLength = 5;
const float yLength = 7;
std::set<VISIBLE_EDGES> edges = {RIGHT, BOTTOM};
}  // namespace PlataformTwelve

namespace PlataformThirdteen {
const float xPosition = 3;
const float yPosition = -26.5;
const float xLength = 6;
const float yLength = 23;
std::set<VISIBLE_EDGES> edges = {TOP};
}  // namespace PlataformThirdteen

namespace PlataformFourteen {
const float xPosition = 3;
const float yPosition = -41;
const float xLength = 6;
const float yLength = 6;
std::set<VISIBLE_EDGES> edges = {RIGHT, BOTTOM};
}  // namespace PlataformFourteen

namespace PlataformFifthteen {
const float xPosition = -4.5;
const float yPosition = -4;
const float xLength = 9;
const float yLength = 20;
std::set<VISIBLE_EDGES> edges = {LEFT, RIGHT, TOP};
}  // namespace PlataformFifthteen

namespace PlataformSixteen {
const float xPosition = -4.5;
const float yPosition = -29;
const float xLength = 9;
const float yLength = 30;
}  // namespace PlataformSixteen

namespace PlataformSeventeen {
const float xPosition = -4.5;
const float yPosition = -47;
const float xLength = 9;
const float yLength = 6;
std::set<VISIBLE_EDGES> edges = {RIGHT, BOTTOM};
}  // namespace PlataformSeventeen

namespace PlataformEighteen {
const float xPosition = -14;
const float yPosition = -30;
const float xLength = 10;
const float yLength = 30;
std::set<VISIBLE_EDGES> edges = {TOP};
}  // namespace PlataformEighteen

namespace PlataformNineteen {
const float xPosition = -14;
const float yPosition = -47.5;
const float xLength = 10;
const float yLength = 5;
std::set<VISIBLE_EDGES> edges = {LEFT, BOTTOM};
}  // namespace PlataformNineteen

namespace PlataformTwenty {
const float xPosition = -22;
const float yPosition = -5;
const float xLength = 6;
const float yLength = 20;
std::set<VISIBLE_EDGES> edges = {LEFT, RIGHT, TOP};
}  // namespace PlataformTwenty

namespace PlataformTwentyOne {
const float xPosition = -22;
const float yPosition = -18.5;
const float xLength = 6;
const float yLength = 7;
std::set<VISIBLE_EDGES> edges = {LEFT};
}  // namespace PlataformTwentyOne

namespace PlataformTwentyTwo {
const float xPosition = -32;
const float yPosition = -26.5;
const float xLength = 14;
const float yLength = 9;
std::set<VISIBLE_EDGES> edges = {BOTTOM, TOP};
}  // namespace PlataformTwentyTwo

namespace PlataformTwentyThree {
const float xPosition = -44.5;
const float yPosition = -12;
const float xLength = 11;
const float yLength = 20;
std::set<VISIBLE_EDGES> edges = {LEFT, RIGHT, TOP};
}  // namespace PlataformTwentyThree

namespace PlataformTwentyFour {
const float xPosition = -44.5;
const float yPosition = -26.5;
const float xLength = 11;
const float yLength = 9;
std::set<VISIBLE_EDGES> edges = {LEFT};
}  // namespace PlataformTwentyFour

namespace PlataformTwentyFive {
const float xPosition = -44.5;
const float yPosition = -40.5;
const float xLength = 11;
const float yLength = 19;
std::set<VISIBLE_EDGES> edges = {LEFT, RIGHT, BOTTOM};
}  // namespace PlataformTwentyFive

namespace PlataformTwentySix {
const float xPosition = -22;
const float yPosition = -26.5;
const float xLength = 6;
const float yLength = 9;
}  // namespace PlataformTwentySix

namespace PlataformTwentySeven {
const float xPosition = -22;
const float yPosition = -38;
const float xLength = 6;
const float yLength = 14;
std::set<VISIBLE_EDGES> edges = {LEFT, TOP};
}  // namespace PlataformTwentySeven

namespace PlataformTwentyEight {
const float xPosition = 47;
const float yPosition = -34;
const float xLength = 5;
const float yLength = 6;
std::set<VISIBLE_EDGES> edges = {LEFT, RIGHT, BOTTOM};
}  // namespace PlataformTwentyEight
#endif
