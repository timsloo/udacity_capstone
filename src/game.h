#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "pac_man.h"
#include "map.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  Game(std::size_t grid_width, std::size_t grid_height, Map map);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  [[nodiscard]] int GetScore() const;

 private:
  PacMan pac_man;
  Map map;

  int score{0};

  void Update();
};

#endif