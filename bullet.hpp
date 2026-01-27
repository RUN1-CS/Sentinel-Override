#ifndef BULLET_HPP
#define BULLET_HPP

#include <ncurses.h>
#include <vector>

#include "asteroid.hpp"

using namespace std;

class bullet{
public:
    bullet(int x, int y, int speed) : x(x), y(y), speed(speed) {}
    int x, y, speed;
    bool hit = false;

    void update(vector<asteroid>& astr){
        if(y >= 0) y -= speed;
        if(check(astr)) y = -1;
    }
private:
    bool check(vector<asteroid>& astr){
        for(auto& a : astr){
            for(int i=0; i<=speed; i++){
                if(a.x == x && a.y == y + i){
                    a.y = LINES + 1;
                    a.status = 1;
                    return true;
                }
            }
        }
        return false;
    }
};

#endif // BULLET_HPP