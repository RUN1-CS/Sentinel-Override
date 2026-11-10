#include <chrono>
#include <iostream>
#include <ncurses.h>
#include <random>
#include <thread>
#include <vector>

#include "classes/asteroid.hpp"
#include "classes/bullet.hpp"
#include "classes/player.hpp"

using namespace std;

int main() {
  try {
    initscr();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
  } catch (const exception &e) {
    cerr << "Error initializing ncurses: " << e.what() << endl;
    return 1;
  }

  int mx = 0, my = 0;
  getmaxyx(stdscr, my, mx);

  player p(mx / 2, my / 2);

  vector<asteroid> asteroids;
  vector<bullet> bullets;

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis_x(0, mx - 1);
  uniform_int_distribution<> dis_y(0, my - 3);
  uniform_int_distribution<> dis_ss(1, 3);

  double frame = 0;

  try {
    for (int i = 0; i < 10; ++i) {
      asteroids.emplace_back(dis_x(gen), dis_y(gen), dis_ss(gen), dis_ss(gen));
    }
    refresh();
  } catch (const exception &e) {
    cerr << "Error generating asteroids: " << e.what() << endl;
    return 1;
  }

  try {
    bool game_over = false;
    while (true) {
      clear();
      p.draw();

      for (auto it = asteroids.begin(); it != asteroids.end();) {
        if (it->isActive()) {
          mvprintw(it->getY(), it->getX(), "O");
          ++it;
        } else if (it->isDestroyed()) {
          mvprintw(it->getY(), it->getX(), "X");
          it->deactivate();
          ++it;
        } else if (it->isInactive()) {
          it = asteroids.erase(it);
          frame += 10;
        }
        refresh();
      }

      for (auto &a : asteroids) {
        a.update(asteroids, frame);

        for (int i = 0; i <= a.getSpeed(); i++) {
          if (p.getX() == a.getX() && p.getY() == a.getY() - i) {
            game_over = true;
          }
        }
      }

      for (auto it = bullets.begin(); it != bullets.end();) {
        it->update(asteroids);
        if (!it->isOutOfBounds()) {
          mvprintw(it->getY(), it->getX(), "|");
        }

        if (it->isOutOfBounds() || it->hasHit()) {
          it = bullets.erase(it);
        } else {
          ++it;
        }
        refresh();
      }

      if (game_over)
        break;

      refresh();

      int ch = getch();
      flushinp();

      if (ch == 'q')
        break; // Exit on 'q'
      else if (ch == 'w')
        p.move(0, -1);
      else if (ch == 's')
        p.move(0, 1);
      else if (ch == 'a')
        p.move(-1, 0);
      else if (ch == 'd')
        p.move(1, 0);
      else if (ch == ' ') {
        bullets.emplace_back(p.getX(), p.getY() - 1, 1);
      }

      if (ch == 'c') {
        /*echo();
        string command = "";
        int newAstr = 0;
        char cmd_char;
        while((cmd_char = getch()) != '\n'){
            command += cmd_char;
        }

        try{
            newAstr = stoi(command);
        }catch(const exception& e){
            newAstr = 0;
        }
        for(int i = 0; i < newAstr; i++){
            asteroids.emplace_back(dis_x(gen), dis_y(gen), dis_ss(gen),
        dis_ss(gen));
        }
        noecho();*/
        asteroids.emplace_back(dis_x(gen), dis_y(gen), dis_ss(gen),
                               dis_ss(gen));
      }

      frame++;

      if (static_cast<int>(frame) % 500 == 0) {
        for (int i = 0; i < 10; ++i) {
          asteroids.emplace_back(dis_x(gen), dis_y(gen), dis_ss(gen),
                                 dis_ss(gen));
        }
      } else if (static_cast<int>(frame) % 100 == 0) {
        for (int i = 0; i < 5; ++i) {
          asteroids.emplace_back(dis_x(gen), dis_y(gen), dis_ss(gen),
                                 dis_ss(gen));
        }
      }

      this_thread::sleep_for(chrono::milliseconds(100));
    }
  } catch (const exception &e) {
    cerr << "Error during game loop: " << e.what() << endl;
  }

  int endGameScreenX = LINES / 2;
  int endGameScreenY = (COLS - 9) / 2;

  clear();
  mvprintw(endGameScreenX, endGameScreenY, "Game Over!");
  mvprintw(endGameScreenX + 1, endGameScreenY, "Final Score: %d",
           static_cast<int>(frame));
  refresh();

  this_thread::sleep_for(chrono::seconds(2));

  flushinp();
  endwin();
  cout << "Thanks for playing! Your final score was: "
       << static_cast<int>(frame) << endl;
  return 0;
}
