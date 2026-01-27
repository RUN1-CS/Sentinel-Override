#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include <ncurses.h>
#include <vector>
#include <cstdlib>

using namespace std;

class asteroid{
public:
    asteroid(int x, int y, int size, int speed) : x(x), y(y), size(size), speed(speed) {}
    int x, y, size, speed;
    // 0 = active, 1 = destroyed 2 = inactive
    int status = 0;

    void update(const vector<asteroid>& astr, double frame){
        if(status) return;
        if(static_cast<int>(frame) % speed == 0 && !status) y += 1;
        if(y >= LINES) {
            y = 0;
            x = rand() % COLS;
        }

        mvprintw(LINES - 2, COLS - 15, "Score: %.0f", frame);
        mvprintw(LINES - 1, COLS - 15, "Asteroids: %lu", astr.size());
    }
};

#endif // ASTEROID_HPP