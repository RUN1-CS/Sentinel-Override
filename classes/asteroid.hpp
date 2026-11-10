#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include <ncurses.h>
#include <vector>

class asteroid {
public:
    asteroid();
    asteroid(int x, int y, int size, int speed);

    void update(const std::vector<asteroid>& asteroids, double frame);

    inline int getX() const { return x; };
    inline int getY() const { return y; };
    inline int getSpeed() const { return speed; };
    inline bool isActive() const { return state == status::active; };
    inline bool isDestroyed() const { return state == status::destroyed; };
    inline bool isInactive() const { return state == status::inactive; };
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