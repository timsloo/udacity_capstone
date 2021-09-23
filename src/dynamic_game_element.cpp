
#include <functional>
#include <iostream>

#include "dynamic_game_element.h"


DynamicGameElement::DynamicGameElement(std::size_t grid_width, std::size_t grid_height)
: grid_width(grid_width),
grid_height(grid_height),
x(grid_width / 2.f),
y(grid_height / 2.f) {}

/**
 * Basic functionality: Move along direction and update x/y position
 */
void DynamicGameElement::Update() {
  switch (direction) {
    case Direction::kUp:
      y -= speed;
      break;

    case Direction::kDown:
      y += speed;
      break;

    case Direction::kLeft:
      x -= speed;
      break;

    case Direction::kRight:
      x += speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  x = fmod(x + grid_width, grid_width);
  y = fmod(y + grid_height, grid_height);
}