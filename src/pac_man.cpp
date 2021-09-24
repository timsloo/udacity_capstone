
#include "pac_man.h"

PacMan::PacMan(std::size_t grid_width, std::size_t grid_height, std::size_t start_x, std::size_t start_y)
        : DynamicGameElement(grid_width, grid_height, start_x, start_y) {
    speed = 0.1;
}

void PacMan::Render(SDL_Renderer *sdl_renderer, int block_width, int block_height) const {
    SDL_Rect block, mouth_block;
    block.w = block_width;
    block.h = block_height;
    block.x = static_cast<int>(x) * block.w;
    block.y = static_cast<int>(y) * block.h;
    mouth_block = block;

    if (state == PacManState::kAlive) {
        // draw yellow rectangle
        SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0x00, 0xFF);
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

void PacMan::Update(Map &map) {
    if (map.at(predictNextCell(direction)) == Map::kWall)
        return;  // do not update if that means hitting walls
    DynamicGameElement::Update();
}
