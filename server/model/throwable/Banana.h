#ifndef BANANA_H
#define BANANA_H
#include <unordered_map>

#include "Throwable.h"
class Duck;

class Banana: public Throwable {
private:
    bool beenStepped;
    void BeStepped(Duck* duck);
    bool IsReadyToBeStepped();

public:
    explicit Banana(TypeItem type);
    ~Banana() = default;
    void Update(const StaticMap& map, float deltaTime) override;
    void CheckCollisionWithDucks(std::unordered_map<PlayerID_t, Duck*>& ducks) override;
};
#endif
