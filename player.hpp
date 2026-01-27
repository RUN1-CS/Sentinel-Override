#include <ncurses.h>

#ifndef PLAYER_HPP
#define PLAYER_HPP

class player {
public:
    player(int x, int y) : x(x), y(y) {}

    void move(int dx, int dy) {
        x += dx;
        y += dy;
    }

    void draw() const {
        mvprintw(y, x, icon == 'V' ? "V" : " ");
    }
    int x, y;
    char icon = 'V';
};

#endif // PLAYER_HPP