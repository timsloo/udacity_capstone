#include "game.h"
#include "utils.h"

#include <iostream>
#include <functional>
#include <memory>
#include "SDL.h"



Game::Game(std::size_t grid_width, std::size_t grid_height, std::size_t num_ghosts)
        : map(grid_width, grid_height) {
    InitDynamicElements(num_ghosts, grid_width, grid_height);
}

Game::Game(std::size_t grid_width, std::size_t grid_height, std::size_t num_ghosts, Map m)
        : map(std::move(m)) {
    InitDynamicElements(num_ghosts, grid_width, grid_height);
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

    // update ghosts
    for (auto& ghost : ghosts){
        ghost->Update(map);
    }

    // PacMan update
    SDL_Point pacman_old{ static_cast<int>(pac_man->x), static_cast<int>(pac_man->y)};
    pac_man->Update(map);
    SDL_Point pacman_new{ static_cast<int>(pac_man->x), static_cast<int>(pac_man->y)};

    // collision checking
    bool collision = false;
    for (auto& ghost: ghosts){
        SDL_Point ghost_pos{static_cast<int>(ghost->x), static_cast<int>(ghost->y)};
        if (ghost_pos == pacman_new){
            collision = true;
            break;
        }
    }
    if (collision) {
        pac_man->state = PacMan::kDead;
    }

    // Check for static elements if position has changed
    if ( !(pacman_old == pacman_new)) {
        switch (Map::StaticGameElement &static_element = map.at(pacman_new)) {
            case Map::kPoint:
                score += 10;
                AdjustGhostSpeed(0.0001);
                static_element = Map::kEmpty;
                break;
            case Map::kPower:
                // TODO: Possible feature
                break;
            case Map::kFruit:
                // TODO: Possible feature
                break;
            default:
                break;
        }
    }

}

int Game::GetScore() const { return score; }

void Game::InitDynamicElements(std::size_t num_ghosts, std::size_t grid_width, std::size_t grid_height) {
    // init pacman
    SDL_Point start_pos = map.getRandomValidPosition(true);
    pac_man = std::make_shared<PacMan>(grid_width, grid_height, start_pos.x, start_pos.y);

    // init ghosts
    for (size_t i = 0; i < num_ghosts; i++) {
        start_pos = map.getRandomValidPosition();
        ghosts.emplace_back(std::make_shared<Ghost>(grid_width, grid_height, start_pos.x, start_pos.y));
    }
}

void Game::AdjustGhostSpeed(float speed_increment) {
    for (auto& ghost : ghosts) {
        ghost->speed += speed_increment;
    }
}

