#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include <ncurses.h>
#include <vector>

class asteroid {
public:
    asteroid();
    asteroid(int x, int y, int size, int speed);

    void update(const std::vector<asteroid>& asteroids, double frame);

    int getX() const;
    int getY() const;
    int getSpeed() const;
    bool isActive() const;
    bool isDestroyed() const;
    bool isInactive() const;
    void destroy();
    void deactivate();

private:
    enum class status {
        active,
        destroyed,
        inactive
    };

    status state = status::active;
    int x, y, size, speed;
};

#endif // ASTEROID_HPP