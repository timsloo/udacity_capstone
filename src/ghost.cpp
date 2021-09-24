//
// Created by tim on 23.09.21.
//

#include "ghost.h"


Ghost::Ghost(std::size_t grid_width, std::size_t grid_height, std::size_t start_x, std::size_t start_y)
        : DynamicGameElement(grid_width, grid_height, start_x, start_y) {};

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

void Ghost::Update(Map &map) {
    DynamicGameElement::Update();
}
