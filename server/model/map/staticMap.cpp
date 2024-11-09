#include "staticMap.h"

#include "mapConstants.h"
enum : int { L, R, B, T };


void StaticMap::AddTransform(const Transform& obj) { plataforms.emplace_back(obj); }
void StaticMap::AddGround(const GroundDto& grd) { grounds.emplace_back(grd); }
/* bool somethingUnderThisPosition(const Vector2D& t) {
     for (int i = t.GetPos().y; i <= limits[1]; i--) {
         Transform t(Vector2D(t.GetPos().x, i), Vector2D(1, 1), 0);
         if (CheckCollision(t)) {
             return true;
         }
     }
     return false;
 }
 void getRandomPosition(float& x, float& y) {
 std::random_device rd;
 std::mt19937 gen(rd());
 std::uniform_int_distribution<> distribX(limits[L], limits[R]);
 std::uniform_int_distribution<> distribY(limits[B], limits[T]);
     x = distribX(gen);
     y = distribY(gen);
 }
*/

void StaticMap::AddEasyLevel() {
    size.emplace_back(FullMapSize::xMapSize);
    size.emplace_back(FullMapSize::yMapSize);

    limits.emplace_back(-static_cast<int>(FullMapSize::xMapSize) / 2);  // izquierda [0]
    limits.emplace_back(FullMapSize::xMapSize / 2);                     // derecha [1]
    limits.emplace_back(-static_cast<int>(FullMapSize::yMapSize) / 2);  // inferior [2]
    limits.emplace_back(FullMapSize::yMapSize / 2);                     // superior [3]

    // plataforma 1
    Transform PlataformOne(Vector2D(PlataformOne::xPosition, PlataformOne::yPosition),
                           Vector2D(PlataformOne::xLength, PlataformOne::yLength), 0);

    GroundDto GROne(PlataformOne, PlataformOne::edges);
    AddGround(GROne);
    // plataforma 2
    Transform PlataformTwo(Vector2D(PlataformTwo::xPosition, PlataformTwo::yPosition),
                           Vector2D(PlataformTwo::xLength, PlataformTwo::yLength), 0);
    GroundDto GRTwo(PlataformTwo, PlataformTwo::edges);
    AddGround(GRTwo);
    // plataforma 3
    Transform PlataformThree(Vector2D(PlataformThree::xPosition, PlataformThree::yPosition),
                             Vector2D(PlataformThree::xLength, PlataformThree::yLength), 0);
    GroundDto GRThree(PlataformThree, PlataformThree::edges);
    AddGround(GRThree);
    // plataforma 4
    Transform PlataformFour(Vector2D(PlataformFour::xPosition, PlataformFour::yPosition),
                            Vector2D(PlataformFour::xLength, PlataformFour::yLength), 0);

    AddTransform(PlataformFour);
    // plataforma 5
    Transform PlataformFive(Vector2D(PlataformFive::xPosition, PlataformFive::yPosition),
                            Vector2D(PlataformFive::xLength, PlataformFive::yLength), 0);
    GroundDto GRFive(PlataformFive, PlataformFive::edges);
    AddGround(GRFive);
    // plataforma 6
    Transform PlataformSix(Vector2D(PlataformSix::xPosition, PlataformSix::yPosition),
                           Vector2D(PlataformSix::xLength, PlataformSix::yLength), 0);
    GroundDto GRSix(PlataformSix, PlataformSix::edges);
    AddGround(GRSix);
    // plataforma 7
    Transform PlataformSeven(Vector2D(PlataformSeven::xPosition, PlataformSeven::yPosition),
                             Vector2D(PlataformSeven::xLength, PlataformSeven::yLength), 0);
    GroundDto GRSeven(PlataformSeven, PlataformSeven::edges);
    AddGround(GRSeven);
    // plataforma 8
    Transform PlataformEight(Vector2D(PlataformEight::xPosition, PlataformEight::yPosition),
                             Vector2D(PlataformEight::xLength, PlataformEight::yLength), 0);
    GroundDto GREight(PlataformEight, PlataformEight::edges);
    AddGround(GREight);
    // plataforma 9
    Transform PlataformNine(Vector2D(PlataformNine::xPosition, PlataformNine::yPosition),
                            Vector2D(PlataformNine::xLength, PlataformNine::yLength), 0);
    GroundDto GRNine(PlataformNine, PlataformNine::edges);
    AddGround(GRNine);
    // plataforma 10
    Transform PlataformTen(Vector2D(PlataformTen::xPosition, PlataformTen::yPosition),
                           Vector2D(PlataformTen::xLength, PlataformTen::yLength), 0);
    GroundDto GRTen(PlataformTen, PlataformTen::edges);
    AddGround(GRTen);
    // plataforma 11
    Transform PlataformEleven(Vector2D(PlataformEleven::xPosition, PlataformEleven::yPosition),
                              Vector2D(PlataformEleven::xLength, PlataformEleven::yLength), 0);
    GroundDto GREleven(PlataformEleven, PlataformEleven::edges);
    AddGround(GREleven);
    // plataforma 12
    Transform PlataformTwelve(Vector2D(PlataformTwelve::xPosition, PlataformTwelve::yPosition),
                              Vector2D(PlataformTwelve::xLength, PlataformTwelve::yLength), 0);
    GroundDto GRTwelve(PlataformTwelve, PlataformTwelve::edges);
    AddGround(GRTwelve);
    // plataforma 13
    Transform PlataformThirdteen(
            Vector2D(PlataformThirdteen::xPosition, PlataformThirdteen::yPosition),
            Vector2D(PlataformThirdteen::xLength, PlataformThirdteen::yLength), 0);
    GroundDto GRThirdteen(PlataformThirdteen, PlataformThirdteen::edges);
    AddGround(GRThirdteen);
    // plataforma 14
    Transform PlataformFourteen(
            Vector2D(PlataformFourteen::xPosition, PlataformFourteen::yPosition),
            Vector2D(PlataformFourteen::xLength, PlataformFourteen::yLength), 0);
    GroundDto GRFourteen(PlataformFourteen, PlataformFourteen::edges);
    AddGround(GRFourteen);
    // plataforma 15
    Transform PlataformFifthteen(
            Vector2D(PlataformFifthteen::xPosition, PlataformFifthteen::yPosition),
            Vector2D(PlataformFifthteen::xLength, PlataformFifthteen::yLength), 0);
    GroundDto GRFifthteen(PlataformFifthteen, PlataformFifthteen::edges);
    AddGround(GRFifthteen);
    // plataforma 16
    Transform PlataformSixteen(Vector2D(PlataformSixteen::xPosition, PlataformSixteen::yPosition),
                               Vector2D(PlataformSixteen::xLength, PlataformSixteen::yLength), 0);
    AddTransform(PlataformSixteen);
    // plataforma 17
    Transform PlataformSeventeen(
            Vector2D(PlataformSeventeen::xPosition, PlataformSeventeen::yPosition),
            Vector2D(PlataformSeventeen::xLength, PlataformSeventeen::yLength), 0);
    GroundDto GRSeventeen(PlataformSeventeen, PlataformSeventeen::edges);
    AddGround(GRSeventeen);
    // plataforma 18
    Transform PlataformEighteen(
            Vector2D(PlataformEighteen::xPosition, PlataformEighteen::yPosition),
            Vector2D(PlataformEighteen::xLength, PlataformEighteen::yLength), 0);
    GroundDto GREighteen(PlataformEighteen, PlataformEighteen::edges);
    AddGround(GREighteen);
    // plataforma 19
    Transform PlataformNineteen(
            Vector2D(PlataformNineteen::xPosition, PlataformNineteen::yPosition),
            Vector2D(PlataformNineteen::xLength, PlataformNineteen::yLength), 0);
    GroundDto GRNineteen(PlataformNineteen, PlataformNineteen::edges);
    AddGround(GRNineteen);
    // plataforma 20
    Transform PlataformTwenty(Vector2D(PlataformTwenty::xPosition, PlataformTwenty::yPosition),
                              Vector2D(PlataformTwenty::xLength, PlataformTwenty::yLength), 0);
    GroundDto GRTwenty(PlataformTwenty, PlataformTwenty::edges);
    AddGround(GRTwenty);
    // plataforma 21
    Transform PlataformTwentyOne(
            Vector2D(PlataformTwentyOne::xPosition, PlataformTwentyOne::yPosition),
            Vector2D(PlataformTwentyOne::xLength, PlataformTwentyOne::yLength), 0);
    GroundDto GRTwentyOne(PlataformTwentyOne, PlataformTwentyOne::edges);
    AddGround(GRTwentyOne);
    // plataforma 22
    Transform PlataformTwentyTwo(
            Vector2D(PlataformTwentyTwo::xPosition, PlataformTwentyTwo::yPosition),
            Vector2D(PlataformTwentyTwo::xLength, PlataformTwentyTwo::yLength), 0);
    GroundDto GRTwentyTwo(PlataformTwentyTwo, PlataformTwentyTwo::edges);
    AddGround(GRTwentyTwo);
    // plataforma 23
    Transform PlataformTwentyThree(
            Vector2D(PlataformTwentyThree::xPosition, PlataformTwentyThree::yPosition),
            Vector2D(PlataformTwentyThree::xLength, PlataformTwentyThree::yLength), 0);
    GroundDto GRTwentyThree(PlataformTwentyThree, PlataformTwentyThree::edges);
    AddGround(GRTwentyThree);
    // plataforma 24
    Transform PlataformTwentyFour(
            Vector2D(PlataformTwentyFour::xPosition, PlataformTwentyFour::yPosition),
            Vector2D(PlataformTwentyFour::xLength, PlataformTwentyFour::yLength), 0);
    GroundDto GRTwentyFour(PlataformTwentyFour, PlataformTwentyFour::edges);
    AddGround(GRTwentyFour);
    // plataforma 25
    Transform PlataformTwentyFive(
            Vector2D(PlataformTwentyFive::xPosition, PlataformTwentyFive::yPosition),
            Vector2D(PlataformTwentyFive::xLength, PlataformTwentyFive::yLength), 0);
    GroundDto GRTwentyFive(PlataformTwentyFive, PlataformTwentyFive::edges);
    AddGround(GRTwentyFive);
    // plataforma 26
    Transform PlataformTwentySix(
            Vector2D(PlataformTwentySix::xPosition, PlataformTwentySix::yPosition),
            Vector2D(PlataformTwentySix::xLength, PlataformTwentySix::yLength), 0);
    AddTransform(PlataformTwentySix);
    // plataforma 27
    Transform PlataformTwentySeven(
            Vector2D(PlataformTwentySeven::xPosition, PlataformTwentySeven::yPosition),
            Vector2D(PlataformTwentySeven::xLength, PlataformTwentySeven::yLength), 0);
    GroundDto GRTwentySeven(PlataformTwentySeven, PlataformTwentySeven::edges);
    AddGround(GRTwentySeven);
    // plataforma 28
    Transform PlataformTwentyEight(
            Vector2D(PlataformTwentyEight::xPosition, PlataformTwentyEight::yPosition),
            Vector2D(PlataformTwentyEight::xLength, PlataformTwentyEight::yLength), 0);
    GroundDto GRTwentyEight(PlataformTwentyEight, PlataformTwentyEight::edges);
    AddGround(GRTwentyEight);
}

void StaticMap::AddTestLevel() {
    Transform unic(Vector2D(TestLevel::xPosition, TestLevel::yPosition),
                   Vector2D(TestLevel::xLength, TestLevel::yLength), 0);
    AddGround(GroundDto(unic, TestLevel::edges));
}

StaticMap::StaticMap(): theme(Theme::Forest) {
    // theme = Theme::Forest;
    size.emplace_back(FullMapSize::xMapSize);
    size.emplace_back(FullMapSize::yMapSize);

    limits.emplace_back(-static_cast<int>(FullMapSize::xMapSize) / 2);  // izquierda [0]
    limits.emplace_back(FullMapSize::xMapSize / 2);                     // derecha [1]
    limits.emplace_back(-static_cast<int>(FullMapSize::yMapSize) / 2);  // inferior [2]
    limits.emplace_back(FullMapSize::yMapSize / 2);                     // superior [3]
    AddTestLevel();
    AddEasyLevel();
}  // recibira el nombre del archivo con el nivel a agregar
// esta en el mapa
std::optional<float> StaticMap::DisplacementOutOfBounds(const Transform& dynamicT) {
    Vector2D posDynamic = dynamicT.GetPos();
    float xDynamic = posDynamic.x;
    float yDynamic = posDynamic.y;

    float radio = (dynamicT.GetSize().y) / 2;

    if (yDynamic - radio < limits[B]) {
        return -1;
    }
    if (xDynamic - radio < limits[L]) {  // caso izquierda
        return limits[L] - (xDynamic - radio);
    }
    if (yDynamic + radio > limits[T]) {  // caso arriba
        return yDynamic + radio - limits[T];
    }
    if (xDynamic + radio > limits[R]) {
        return xDynamic + radio - limits[R];
    }
    return std::nullopt;  // El objeto está dentro de los límites
}

bool StaticMap::IsOnTheFloor(const Transform& dynamicT) {
    Vector2D dir = Vector2D::Down();
    float len = (dynamicT.GetSize().y) / 2;
    float margen = (80 * len / 100);
    Vector2D posLeft(dynamicT.GetPos().x - margen, dynamicT.GetPos().y);
    Vector2D posRight(dynamicT.GetPos().x + margen, dynamicT.GetPos().y);

    return std::any_of(grounds.begin(), grounds.end(),
                       [&dynamicT, &dir, len, posLeft, posRight](const auto& ground) {
                           bool left = Collision::Raycast(posLeft, dir, len + 0.2f, ground.mySpace);
                           bool right =
                                   Collision::Raycast(posRight, dir, len + 0.2f, ground.mySpace);
                           return left || right;
                       });
}

std::optional<Transform> StaticMap::CheckCollision(const Transform& dynamicT) {
    auto it = std::find_if(grounds.begin(), grounds.end(), [&dynamicT](const auto& ground) {
        return Collision::RectCollision(dynamicT, ground.mySpace);
    });

    if (it != grounds.end()) {
        return it->mySpace;  // Colisión detectada
    }
    return std::nullopt;  // Sin colisiones
}

std::vector<Vector2D> StaticMap::GetPlayersSpawnPoints() {
    std::vector<Vector2D> safePositions;

    // for (int i = limits[0]; i <= limits[3]; i ++){}
    // Posiciones seguras hardcodeadas
    // 41 6
    // -4 12
    // -34 43
    // -42 6
    /*while (safePositions.size() < 4) {
        float x, y;
        getRandomPosition(x, y);
        Vector2D vec(x, y);
        if (somethingUnderThisPosition(vec)) {
            safePositions.emplace_back(vec);
        }
    }*/
    safePositions.emplace_back(Vector2D(41, 6));
    safePositions.emplace_back(Vector2D(-4, 12));
    safePositions.emplace_back(Vector2D(-34, 43));
    safePositions.emplace_back(Vector2D(-42, 6));

    return safePositions;
}

GameSceneDto StaticMap::GetScene() { return GameSceneDto(theme, plataforms, grounds); }
