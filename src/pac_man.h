
#ifndef PACMAN_H
#define PACMAN_H

#include "dynamic_game_element.h"
#include "map.h"

class PacMan : public DynamicGameElement {
public:
    enum PacManState {
        kAlive
    };

    PacMan(int grid_width, int grid_height);

    PacManState state = PacManState::kAlive;

    void Render(SDL_Renderer* renderer, int block_width, int block_height) const override;
    // void Update(const Map& map);

private:

};


#endif //PACMAN_H
