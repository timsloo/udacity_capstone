
#ifndef GHOST_H
#define GHOST_H

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

};


#endif