#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "dynamic_game_element.h"

class Renderer {
public:
    Renderer(const std::size_t screen_width, const std::size_t screen_height,
             const std::size_t grid_width, const std::size_t grid_height);

    ~Renderer();

    // void Render(const std::vector<Renderable>& renderables);
    void Render(const Renderable& renderable, const DynamicGameElement& game_element);

    void UpdateWindowTitle(int score, int fps);

private:
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;

    const std::size_t screen_width;
    const std::size_t screen_height;
    const std::size_t grid_width;
    const std::size_t grid_height;
};

#endif