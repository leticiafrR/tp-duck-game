#include "Rate.h"

Rate::Rate(int target): target(target) {}
Rate::~Rate() = default;

float Rate::GetDeltaTime() const { return 1.0f / target; }

float Rate::GetMiliseconds() const { return 1000.0f / target; }
