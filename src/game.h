#ifndef GAME_H
#define GAME_H

#include <random>
#include <vector>
#include <memory>
#include "SDL.h"

#include "controller.h"
#include "ghost.h"
#include "renderer.h"
#include "pac_man.h"
#include "map.h"

class Game {
public:
    Game(std::size_t grid_width, std::size_t grid_height, std::size_t num_ghosts);

    Game(std::size_t grid_width, std::size_t grid_height, std::size_t num_ghosts, Map map);

    void Run(Controller const &controller, Renderer &renderer,
             std::size_t target_frame_duration);

    [[nodiscard]] int GetScore() const;

private:
    void Update();

    void InitDynamicElements(std::size_t num_ghosts, std::size_t grid_width, std::size_t grid_height);

    void AdjustGhostSpeed(float speed_increment);

    std::shared_ptr<PacMan> pac_man;
    std::vector<std::shared_ptr<Ghost>> ghosts;
    Map map;

    int score{0};

};

#endif