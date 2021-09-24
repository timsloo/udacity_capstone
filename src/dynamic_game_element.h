#ifndef DYNAMIC_GAME_ELEMENT_H
#define DYNAMIC_GAME_ELEMENT_H

#include <vector>
#include <map.h>
#include "SDL.h"
#include "renderable.h"

class DynamicGameElement : public Renderable{
public:
    enum class Direction {
        kUp, kDown, kLeft, kRight
    };

    DynamicGameElement(std::size_t grid_width, std::size_t grid_height, std::size_t start_x, std::size_t start_y);

    Direction direction = Direction::kUp;

    void Update(Map &map);

    float speed{0.1f};
    bool alive{true};
    float x;
    float y;

private:
    [[nodiscard]] SDL_Point predictNextCell() const;

    std::size_t grid_width;
    std::size_t grid_height;
};

#endif