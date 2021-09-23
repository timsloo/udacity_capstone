
#include <functional>
#include <iostream>

#include "dynamic_game_element.h"

bool operator==(const SDL_Point& lhs, const SDL_Point& rhs){
    return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

DynamicGameElement::DynamicGameElement(std::size_t grid_width, std::size_t grid_height)
        : grid_width(grid_width),
          grid_height(grid_height),
          x(grid_width / 2.f),
          y(grid_height / 2.f) {}


void DynamicGameElement::Update(Map &map) {
    if (map.at(predictNextCell()) == Map::kWall)
        return;  // do not update if that means hitting walls

    switch (direction) {
        case Direction::kUp:
            y -= speed;
            break;

        case Direction::kDown:
            y += speed;
            break;

        case Direction::kLeft:
            x -= speed;
            break;

        case Direction::kRight:
            x += speed;
            break;
    }

    // Wrap the Snake around to the beginning if going off of the screen.
    x = fmod(x + grid_width, grid_width);
    y = fmod(y + grid_height, grid_height);
}

SDL_Point DynamicGameElement::predictNextCell() const {
    SDL_Point next_cell{static_cast<int>(x), static_cast<int>(y)};

    switch (direction) {
        case Direction::kUp:
            next_cell.y -= 1;
            break;
        case Direction::kDown:
            next_cell.y += 1;
            break;
        case Direction::kLeft:
            next_cell.x -= 1;
            break;
        case Direction::kRight:
            next_cell.x += 1;
            break;
    }

    next_cell.x = fmod(next_cell.x + grid_width, grid_width);
    next_cell.y = fmod(next_cell.y + grid_height, grid_height);

    return next_cell;
}
