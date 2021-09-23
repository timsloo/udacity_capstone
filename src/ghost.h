
#ifndef GHOST_H
#define GHOST_H

#include "dynamic_game_element.h"

class Ghost : public DynamicGameElement{
public:
    enum GhostState {dangerous, vulnerable, dead};

    Ghost(int grid_width, int grid_height) : DynamicGameElement(grid_width, grid_height);

    GhostState state = GhostState::dangerous;

private:

};


#endif GHOST_H
