#ifndef MAP_H
#define MAP_H

#include <cstddef>
#include <random>
#include <string>
#include "SDL.h"
#include "renderable.h"

class Map : public Renderable {
public:
    enum StaticGameElement {
        kWall, kPoint, kPower, kFruit, kEmpty
    };

    Map(std::size_t grid_width, std::size_t grid_height);

    Map(std::size_t grid_width, std::size_t grid_height, const std::string &filename);

    Map(const Map &other);

    Map &operator=(const Map &other);

    Map(Map &&other) noexcept;

    Map &operator=(Map &&other);

    ~Map() = default;

    StaticGameElement &at(std::size_t x, std::size_t y);

    StaticGameElement &at(SDL_Point point);

    void Render(SDL_Renderer* renderer, int block_width, int block_height) const override;

    SDL_Point getRandomValidPosition(bool constraintOnlyReachable=false);

    void readMapFromFile(const std::string &filename);

private:
    void static ScaleRectangleInGrid(SDL_Rect &block, float scalingFactor);

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
