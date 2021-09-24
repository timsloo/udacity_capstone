
#ifndef PACMAN_RENDERABLE_H
#define PACMAN_RENDERABLE_H

#include "SDL_render.h"

class Renderable {
public:
    virtual void Render(SDL_Renderer *renderer, int block_width, int block_height) const = 0;
};


#endif //PACMAN_RENDERABLE_H
