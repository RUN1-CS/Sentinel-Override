#ifndef BULLET_HPP
#define BULLET_HPP

#include <vector>

#include "asteroid.hpp"

class bullet {
public:
    bullet(int x, int y, int speed);

    void update(std::vector<asteroid>& asteroids);

    int getX() const;
    int getY() const;
    bool hasHit() const;
    bool isOutOfBounds() const;

private:
    bool checkCollision(std::vector<asteroid>& asteroids);

    int x;
    int y;
    int speed;
    bool hit = false;
};

#endif // BULLET_HPP