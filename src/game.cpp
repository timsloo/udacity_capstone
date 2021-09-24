#include "game.h"

#include <iostream>
#include <functional>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
        : pac_man(std::make_shared<PacMan>(grid_width, grid_height)),
          map(grid_width, grid_height) {
}

Game::Game(std::size_t grid_width, std::size_t grid_height, Map m)
        : pac_man(std::make_shared<PacMan>(grid_width, grid_height)),
          map(std::move(m)) {
}


void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;
    bool running = true;

    std::vector<std::shared_ptr<DynamicGameElement>> game_elements(ghosts.begin(), ghosts.end());
    game_elements.emplace_back(pac_man);

    while (running) {
        frame_start = SDL_GetTicks();

        // Input, Update, Render - the main game loop.
        controller.HandleInput(running, *pac_man);
        Update();
        renderer.Render(map, game_elements);

        frame_end = SDL_GetTicks();

        // Keep track of how long each loop through the input/update/render cycle
        // takes.
        frame_count++;
        frame_duration = frame_end - frame_start;

        // Every 200ms second, update the window title.
        if (frame_end - title_timestamp >= 200) {
            renderer.UpdateWindowTitle(score, frame_count);
            frame_count = 0;
            title_timestamp = frame_end;
        }

        // If the time for this frame is too small (i.e. frame_duration is
        // smaller than the target ms_per_frame), delay the loop to
        // achieve the correct frame rate.
        if (frame_duration < target_frame_duration) {
            SDL_Delay(target_frame_duration - frame_duration);
        }
    }
}


void Game::Update() {
    if (pac_man->state != PacMan::PacManState::kAlive) return;

    pac_man->Update(map);

    int new_x = static_cast<int>(pac_man->x);
    int new_y = static_cast<int>(pac_man->y);

    // Check for static elements

    switch (Map::StaticGameElement &static_element = map.at(new_x, new_y)) {
        case Map::kPoint:
            score += 10;
            pac_man-> speed += 0.0001; // ToDO: eher speed der Geister anpassen
            static_element = Map::kEmpty;
            break;
        case Map::kPower:
            // TODO
            break;
        case Map::kFruit:
            // TODO
            break;
        default:
            break;
    }
}

int Game::GetScore() const { return score; }

