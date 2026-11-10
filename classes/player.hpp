#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <ncurses.h>

class player {
public:
    player(int x, int y);
    void move(int dx, int dy);
    inline void draw() const { mvprintw(y, x, "%c", icon); };
    inline int getX() const { return x; };
    inline int getY() const { return y; };

private:
    int x;
    int y;
    char icon = 'V';
};

#endif // PLAYER_HPP