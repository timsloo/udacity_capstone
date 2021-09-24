
#ifndef GHOST_H
#define GHOST_H

#include <random>
#include "dynamic_game_element.h"
#include "renderable.h"

class Ghost : public DynamicGameElement {
public:
    enum GhostState {
        kDangerous, kVulnerable, kDead
    };

    Ghost(std::size_t grid_width, std::size_t grid_height, std::size_t start_x, std::size_t start_y);

    GhostState state = GhostState::kDangerous;

    void Render(SDL_Renderer *renderer, int block_width, int block_height) const override;

    void Update(Map& map);

private:
    std::vector<DynamicGameElement::Direction> PossibleDirections(Map &map,  bool exclude_backward);
    SDL_Point position_last_direction_update{-1, -1};

    std::random_device dev;
    std::mt19937 engine;
};


#endif