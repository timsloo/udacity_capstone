#ifndef DYNAMIC_GAME_ELEMENT_H
#define DYNAMIC_GAME_ELEMENT_H

#include <vector>
#include "SDL.h"

class DynamicGameElement {  // later: Renderable
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  DynamicGameElement(std::size_t grid_width, std::size_t grid_height);

  Direction direction = Direction::kUp;

  void Update();

  float speed{0.1f};
  bool alive{true};
  float x;
  float y;

 private:
  std::size_t grid_width;
  std::size_t grid_height;
};

#endif