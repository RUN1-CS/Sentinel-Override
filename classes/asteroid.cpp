#include "asteroid.hpp"

#include <cstdlib>

asteroid::asteroid() {
    x = rand() % COLS;
    y = 0;
    size = 1 + rand() % 3;
    speed = 1 + rand() % 5;
}

asteroid::asteroid(int x, int y, int size, int speed)
    : x(x), y(y), size(size), speed(speed) {}

void asteroid::update(const std::vector<asteroid>& asteroids, double frame) {
    if (!isActive()) {
        return;
    }

    if (speed > 0 && static_cast<int>(frame) % speed == 0) {
        ++y;
    }
    if (y >= LINES) {
        y = 0;
        x = rand() % COLS;
    }

    mvprintw(LINES - 2, COLS - 15, "Score: %.0f", frame);
    mvprintw(LINES - 1, COLS - 15, "Asteroids: %lu", asteroids.size());
}

int asteroid::getX() const {
    return x;
}

int asteroid::getY() const {
    return y;
}

int asteroid::getSpeed() const {
    return speed;
}

bool asteroid::isActive() const {
    return state == status::active;
}

bool asteroid::isDestroyed() const {
    return state == status::destroyed;
}

bool asteroid::isInactive() const {
    return state == status::inactive;
}

void asteroid::destroy() {
    if (isActive()) {
        state = status::destroyed;
    }
}

void asteroid::deactivate() {
    if (isDestroyed()) {
        state = status::inactive;
    }
}