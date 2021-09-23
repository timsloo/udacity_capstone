//
// Created by tim on 23.09.21.
//

#ifndef MAP_H
#define MAP_H

#include <cstddef>
#include <random>
#include <string>
#include "SDL.h"

class Map{
public:
    enum StaticGameElement {kWall, kPoint, kPower, kFruit, kEmpty};

    Map(std::size_t grid_width, std::size_t grid_height);
    Map(std::size_t grid_width, std::size_t grid_height, const std::string& filename);
    Map(const Map& other);
    Map& operator=(const Map& other);
    Map(Map&& other);
    Map& operator=(Map&& other);
    ~Map() = default;

    StaticGameElement& at(std::size_t x, std::size_t y);
    StaticGameElement& at(SDL_Point point);


private:
    void readMapFromFile(const std::string& filename);

    std::size_t grid_width;
    std::size_t grid_height;
    std::vector<StaticGameElement> grid2d;

    // for generation of random numbers
    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_w;
    std::uniform_int_distribution<int> random_h;
};

#endif //MAP_H
