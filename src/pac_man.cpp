//
// Created by tim on 23.09.21.
//

#include "pac_man.h"

PacMan::PacMan(int grid_width, int grid_height) : DynamicGameElement(grid_width, grid_height) {

}

void PacMan::Render(SDL_Renderer *sdl_renderer, int block_width, int block_height) const {
    SDL_Rect block;
    block.w = block_width;
    block.h = block_height;
    block.x = static_cast<int>(x) * block.w;
    block.y = static_cast<int>(y) * block.h;
    if (state == PacManState::kAlive) {
        SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
    } else {
        SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
    }
    SDL_RenderFillRect(sdl_renderer, &block);
}
