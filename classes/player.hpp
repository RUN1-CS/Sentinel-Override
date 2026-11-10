#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <ncurses.h>

class player {
public:
    player(int x, int y);
    void move(int dx, int dy);
    void draw() const;
    int getX() const;
    int getY() const;

private:
    int x;
    int y;
    char icon = 'V';
};

#endif // PLAYER_HPP