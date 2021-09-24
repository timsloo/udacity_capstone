//
// Created by tim on 24.09.21.
//

#ifndef PACMAN_UTILS_H
#define PACMAN_UTILS_H

bool operator==(const SDL_Point &lhs, const SDL_Point &rhs) {
    return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

#endif //PACMAN_UTILS_H
