//
// Created by tim on 23.09.21.
//

#include "pac_man.h"

PacMan::PacMan(int grid_width, int grid_height) : DynamicGameElement(grid_width, grid_height) {

}

void PacMan::Render(SDL_Renderer *sdl_renderer, int block_width, int block_height) const {
    SDL_Rect block, mouth_block;
    block.w = block_width;
    block.h = block_height;
    block.x = static_cast<int>(x) * block.w;
    block.y = static_cast<int>(y) * block.h;
    mouth_block = block;

    if (state == PacManState::kAlive) {
        // draw blue rectangle
        SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
        SDL_RenderFillRect(sdl_renderer, &block);

        // draw mouth by black overlay in direction of travel
        SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
        switch (direction) {
            case Direction::kUp:
                block.x = block.x + 0.25 * block.w;
                block.w = block.w * 0.5f;
                block.h = block.h * 0.75f;
                break;
            case Direction::kDown:
                block.x = block.x + 0.25 * block.w;
                block.y = block.y + 0.25 * block.h;
                block.w = block.w * 0.5f;
                block.h = block.h * 0.75f;
                break;
            case Direction::kLeft:
                block.y = block.y + 0.25 * block.h;
                block.w = block.w * 0.75f;
                block.h = block.h * 0.5f;
                break;
            case Direction::kRight:
                block.x = block.x + 0.25 * block.w;
                block.y = block.y + 0.25 * block.h;
                block.w = block.w * 0.75f;
                block.h = block.h * 0.5f;
                break;
        }
        SDL_RenderFillRect(sdl_renderer, &block);
    } else {
        SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(sdl_renderer, &block);
    }
}
