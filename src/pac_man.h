
#ifndef PACMAN_H
#define PACMAN_H

#include "dynamic_game_element.h"
#include "map.h"

class PacMan : public DynamicGameElement {
public:
    enum PacManState {
        kAlive, kDead
    };

    PacMan(std::size_t grid_width, std::size_t grid_height, std::size_t start_x, std::size_t start_y);

    PacManState state = PacManState::kAlive;

    void Render(SDL_Renderer *renderer, int block_width, int block_height) const override;

    void Update(Map &map);

private:

};


#endif //PACMAN_H
