
#ifndef PACMAN_H
#define PACMAN_H

#include "dynamic_game_element.h"
#include "map.h"

class PacMan : public DynamicGameElement{
public:
    enum PacManState {kAlive};

    PacMan(int grid_width, int grid_height);

    PacManState state = PacManState::kAlive;

    void Update(const Map& map);

private:

};


#endif //PACMAN_H
