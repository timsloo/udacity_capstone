//
// Created by tim on 23.09.21.
//

#include <algorithm>
#include "ghost.h"
#include "utils.h"


Ghost::Ghost(std::size_t grid_width, std::size_t grid_height, std::size_t start_x, std::size_t start_y)
        : DynamicGameElement(grid_width, grid_height, start_x, start_y),
          engine(dev()) {};

void Ghost::Render(SDL_Renderer *renderer, int block_width, int block_height) const {
    SDL_Rect block, eyes_block;
    block.w = block_width;
    block.h = block_height;
    block.x = static_cast<int>(x) * block.w;
    block.y = static_cast<int>(y) * block.h;
    eyes_block = block;

    if (state == GhostState::kDangerous) {
        // draw blue rectangle
        SDL_SetRenderDrawColor(renderer, 0x00, 0x7A, 0xCC, 0xFF);
        SDL_RenderFillRect(renderer, &block);

        // draw left eye
        block.y = block.y + block_height * 0.25;
        block.x = block.x + block_width * 0.125;
        block.w = block_width * 0.25f;
        block.h = block_height * 0.25f;
        SDL_SetRenderDrawColor(renderer, 0x1E, 0x1E, 0x1E, 0xFF);
        SDL_RenderFillRect(renderer, &block);

        // draw right eye
        block.x = block.x + block_width * 0.5;
        SDL_SetRenderDrawColor(renderer, 0x1E, 0x1E, 0x1E, 0xFF);
        SDL_RenderFillRect(renderer, &block);
    }
}

std::vector<DynamicGameElement::Direction> Ghost::PossibleDirections(Map &map, bool exclude_backward) {
    // possible directions are those that do not collide with walls
    std::vector<DynamicGameElement::Direction> possible_directions;
    Direction backward = oppositeDirection(direction);

    for (auto d : DynamicGameElement::Direction_ALL) {
        if (exclude_backward && (d == backward))
            continue;
        if (map.at(predictNextCell(d)) != Map::kWall)
            possible_directions.emplace_back(d);
    }
    return possible_directions;
}

void Ghost::Update(Map &map) {
    SDL_Point curr_pos{static_cast<int>(x), static_cast<int>(y)};
    if (!(curr_pos == position_last_direction_update)){   // only update direction if cell has changed since last update
        position_last_direction_update = curr_pos;

        // chose randomized direction without crashing into walls
        // strategy: higher probability of following direction than making turns
        // strategy: only make 180 degree turn if no other option available
        std::vector<DynamicGameElement::Direction> direction_set = PossibleDirections(map, true);

        bool forward_included = false;
        for (auto &collision_free_direction : direction_set) {  // TODO: Use std::find but how??
            if (direction == collision_free_direction)
                forward_included = true;
        }

        switch (direction_set.size()) {
            case 0:
                direction = oppositeDirection(direction);
                break;
            case 1:
                direction = direction_set.at(0);
                break;
            default: // >= 2
                std::uniform_real_distribution<double> dist(0, 1);
                if (!forward_included) { // random choice
                    std::uniform_int_distribution<int> dist(0, direction_set.size() - 1);
                    direction = direction_set.at(dist(engine));
                } else if (dist(engine) > 0.7) {  // 30% chance of not going forward
                    direction_set.erase(std::remove(direction_set.begin(), direction_set.end(), direction),
                                        direction_set.end());
                    std::uniform_int_distribution<int> dist(0, direction_set.size() - 1);
                    direction = direction_set.at(dist(engine));
                }
                break;
        }
    }

    DynamicGameElement::Update();
}

