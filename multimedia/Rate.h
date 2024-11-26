#ifndef RATE_H
#define RATE_H

class Rate {
private:
    int target;

public:
    explicit Rate(int target): target(target) {}
    ~Rate() = default;

    float GetDeltaTime() const { return 1.0f / target; }

    float GetMiliseconds() const { return 1000.0f / target; }
};

#endif
