#ifndef DYNAMIC_GAME_ELEMENT_H
#define DYNAMIC_GAME_ELEMENT_H

#include <vector>
#include "SDL.h"

class DynamicGameElement {  // later: Renderable
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  DynamicGameElement(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        x(grid_width / 2),
        y(grid_height / 2) {}

  void Update();

  Direction direction = Direction::kUp;

  float speed{0.1f};
  bool alive{true};
  float x;
  float y;

 private:
  int grid_width;
  int grid_height;
};

#endif