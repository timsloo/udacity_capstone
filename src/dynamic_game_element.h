#ifndef DYNAMIC_GAME_ELEMENT_H
#define DYNAMIC_GAME_ELEMENT_H

#include <vector>
#include <map.h>
#include "SDL.h"

#include "renderable.h"

class DynamicGameElement : public Renderable {
public:
    enum class Direction {
        kUp, kDown, kLeft, kRight

    };

    static constexpr std::initializer_list<Direction> Direction_ALL = {Direction::kUp, Direction::kDown,
                                                                       Direction::kLeft,
                                                                       Direction::kRight}; // for iterating over element

    DynamicGameElement(std::size_t grid_width, std::size_t grid_height, std::size_t start_x, std::size_t start_y);

    static Direction oppositeDirection(Direction direc);

    Direction direction = Direction::kUp;

    float speed;
    float x;
    float y;

private:
    std::size_t grid_width;
    std::size_t grid_height;

protected:
    [[nodiscard]] SDL_Point predictNextCell(DynamicGameElement::Direction direc) const;

    virtual void Update();
};

#endif