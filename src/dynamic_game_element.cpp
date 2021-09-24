#include "dynamic_game_element.h"

#include <iostream>



DynamicGameElement::DynamicGameElement(std::size_t grid_width, std::size_t grid_height, std::size_t start_x, std::size_t start_y)
        : grid_width(grid_width),
          grid_height(grid_height),
          x(start_x),
          y(start_y) {}


void DynamicGameElement::Update() {

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

SDL_Point DynamicGameElement::predictNextCell(DynamicGameElement::Direction direc) const {
    SDL_Point next_cell{static_cast<int>(x), static_cast<int>(y)};

    switch (direc) {
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

DynamicGameElement::Direction DynamicGameElement::oppositeDirection(DynamicGameElement::Direction direc) {
    Direction opposite;
    switch(direc){

        case Direction::kUp:
            opposite = Direction::kDown;
            break;
        case Direction::kDown:
            opposite = Direction::kUp;
            break;
        case Direction::kLeft:
            opposite = Direction::kRight;
            break;
        case Direction::kRight:
            opposite = Direction::kLeft;
            break;
    }
    return opposite;
}
