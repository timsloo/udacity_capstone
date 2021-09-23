#include "game.h"

#include <iostream>
#include <functional>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
        : pac_man(grid_width, grid_height),
          map(grid_width, grid_height) {
}

Game::Game(std::size_t grid_width, std::size_t grid_height, Map m)
        : pac_man(grid_width, grid_height),
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

    std::vector<std::reference_wrapper<Renderable>> renderables;
    renderables.emplace_back(std::ref(pac_man));

    while (running) {
        frame_start = SDL_GetTicks();

        // Input, Update, Render - the main game loop.
        controller.HandleInput(running, pac_man);
        Update();
        renderer.Render(renderables);

        frame_end = SDL_GetTicks();

        // Keep track of how long each loop through the input/update/render cycle
        // takes.
        frame_count++;
        frame_duration = frame_end - frame_start;

        // After every second, update the window title.
        if (frame_end - title_timestamp >= 1000) {
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
    if (pac_man.state != PacMan::PacManState::kAlive) return;

    pac_man.Update(map);

    int new_x = static_cast<int>(pac_man.x);
    int new_y = static_cast<int>(pac_man.y);

    // Check if there's food over here
    /*
    if (food.x == new_x && food.y == new_y) {
        // increase speed
        pac_man.speed += 0.02;
    }
     */
}

int Game::GetScore() const { return score; }

