#include "bullet.hpp"

bullet::bullet(int x, int y, int speed)
    : x(x), y(y), speed(speed) {}

void bullet::update(std::vector<asteroid>& asteroids) {
    if (y < 0) {
        return;
    }

    y -= speed;
    if (checkCollision(asteroids)) {
        y = -1;
    }
}

bool bullet::checkCollision(std::vector<asteroid>& asteroids) {
    for (auto& current : asteroids) {
        for (int offset = 0; offset <= speed; ++offset) {
            if (current.isActive() && current.getX() == x &&
                current.getY() == y + offset) {
                current.destroy();
                hit = true;
                return true;
            }
        }
    }
    return false;
}