#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "dynamic_game_element.h"

class Controller {
 public:
  void HandleInput(bool &running, DynamicGameElement &element) const;

 private:
  void ChangeDirection(DynamicGameElement &snake, DynamicGameElement::Direction input) const;
};

#endif