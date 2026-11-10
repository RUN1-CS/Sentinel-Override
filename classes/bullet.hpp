#ifndef BULLET_HPP
#define BULLET_HPP

#include <vector>

#include "asteroid.hpp"

class bullet {
public:
    bullet(int x, int y, int speed);

    void update(std::vector<asteroid>& asteroids);

    inline int getX() const { return x; };
    inline int getY() const { return y; };
    inline bool hasHit() const { return hit; };
    inline bool isOutOfBounds() const { return y < 0; };

private:
    bool checkCollision(std::vector<asteroid>& asteroids);

    int x;
    int y;
    int speed;
    bool hit = false;
};

#endif // BULLET_HPP