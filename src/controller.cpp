#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

void Controller::ChangeDirection(DynamicGameElement &game_element, DynamicGameElement::Direction input) const {
    game_element.direction = input;
}

void Controller::HandleInput(bool &running, DynamicGameElement &element) const {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            running = false;
        } else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_UP:
                    ChangeDirection(element, DynamicGameElement::Direction::kUp);
                    break;

                case SDLK_DOWN:
                    ChangeDirection(element, DynamicGameElement::Direction::kDown);
                    break;

                case SDLK_LEFT:
                    ChangeDirection(element, DynamicGameElement::Direction::kLeft);
                    break;

                case SDLK_RIGHT:
                    ChangeDirection(element, DynamicGameElement::Direction::kRight);
                    break;
            }
        }
    }
}