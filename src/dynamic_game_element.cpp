#include "dynamic_game_element.h"
#include <functional>
#include <iostream>

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