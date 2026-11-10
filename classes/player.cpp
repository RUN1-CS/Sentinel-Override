#include "player.hpp"

#include <random>

player::player(int x, int y) : x(x), y(y) {
  std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<int> dist(0, 5);
  static constexpr char icons[] = {'V', 'X', 'A', '|', 'C', '0'};
  icon = icons[dist(rng)];
}

void player::move(int dx, int dy) {
  x += dx;
  y += dy;
}