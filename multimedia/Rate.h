#ifndef RATE_H
#define RATE_H

class Rate {
private:
    int target;

public:
    explicit Rate(int target);
    ~Rate();

    float GetDeltaTime() const;

    float GetMiliseconds() const;
};

#endif
