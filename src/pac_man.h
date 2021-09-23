
#ifndef PACMAN_H
#define PACMAN_H

#include "dynamic_game_element.h"

class PacMan : public DynamicGameElement{
public:
    enum PacManState {alive};

    PacMan(int grid_width, int grid_height) : DynamicGameElement(grid_width, grid_height) {};


    PacManState state = PacManState::alive;

private:

};


#endif //PACMAN_H
