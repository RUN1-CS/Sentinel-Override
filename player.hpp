#include <ncurses.h>
#include <random>

#ifndef PLAYER_HPP
#define PLAYER_HPP

class player {
public:
    player(int x, int y) : x(x), y(y) {
        mt19937 rng(random_device{}());
        uniform_int_distribution<int> dist(0, 5);
        switch (dist(rng)) {
            case 0: icon = 'V'; break;
            case 1: icon = 'X'; break;
            case 2: icon = 'A'; break;
            case 3: icon = '|'; break;
            case 4: icon = 'C'; break;
            case 5: icon = '0'; break;
        }
    }

    void move(int dx, int dy) {
        x += dx;
        y += dy;
    }

    void draw() const {
        mvprintw(y, x, "%c", icon);
    }
    int x, y;
    char icon = 'V';
};

#endif // PLAYER_HPP