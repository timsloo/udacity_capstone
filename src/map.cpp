//
// Created by tim on 23.09.21.
//

#include <fstream>
#include <string>
#include <exception>
#include "map.h"


Map::Map(std::size_t grid_width, std::size_t grid_height)
        : grid_width(grid_width),
          grid_height(grid_height),
          grid2d(grid_width * grid_height),
          engine(dev()),
          random_w(0, static_cast<int>(grid_width - 1)),
          random_h(0, static_cast<int>(grid_height - 1)) {

    for (auto &cell : grid2d) {
        cell = Map::kPoint;
    }
    // TODO: initialize other random cells!
}

Map::Map(std::size_t grid_width, std::size_t grid_height, const std::string &path)
        : Map(grid_width, grid_height) {
    readMapFromFile(path);
}


Map::Map(const Map &other)
        : grid_width(other.grid_width),
          grid_height(other.grid_height),
          grid2d(other.grid2d), // uses std::vector deep copy
          engine(dev()),
          random_w(other.random_w),
          random_h(other.random_h) {}

Map &Map::operator=(const Map &other) {
    if (&other == this)
        return *this;

    grid_width = other.grid_width;
    grid_height = other.grid_height;
    grid2d = other.grid2d;  // uses std::vector deep copy
    random_w = other.random_w;
    random_h = other.random_h;

    return *this;
}

Map::Map(Map &&other)
        : grid_width(other.grid_width),
          grid_height(other.grid_height),
          grid2d(std::move(other.grid2d)),
          engine(dev()),
          random_w(other.random_w),
          random_h(other.random_h) {

    other.grid_width = 0;
    other.grid_height = 0;

}

Map &Map::operator=(Map &&other) {
    if (&other == this)
        return *this;

    grid_width = other.grid_width;
    grid_height = other.grid_height;
    grid2d = std::move(other.grid2d);  // uses std::vector deep copy
    random_w = other.random_w;
    random_h = other.random_h;

    return *this;
}


Map::StaticGameElement &Map::at(std::size_t x, std::size_t y) {
    return grid2d.at(y * grid_width + x);
}

Map::StaticGameElement &Map::at(SDL_Point point) {
    return this->at(point.x, point.y);
}

void Map::readMapFromFile(const std::string &path) {
    std::ifstream map_file(path);
    if (map_file) {
        std::string line;
        std::size_t line_counter = 0;
        std::size_t character_counter = 0;
        while (std::getline(map_file, line)) {

            if (line.size() != grid_width)
                throw std::runtime_error(
                        "Input File " + path + ": Number of characters in a line does not match grid width");
            if (line_counter >= grid_height)
                throw std::runtime_error(
                        "Input File " + path + ": Number of lines does not match grid height");

            for (auto &character : line) {
                switch (character) {
                    case '#':
                        this->at(character_counter, line_counter) = Map::kWall;
                        break;
                    case '-':
                        this->at(character_counter, line_counter) = Map::kPoint;
                        break;
                    default:
                        this->at(character_counter, line_counter) = Map::kEmpty;
                }
                character_counter++;
            }
            line_counter++;
            character_counter = 0;
        }
    }
}

void Map::Render(SDL_Renderer *renderer, int block_width, int block_height) const {
    SDL_Rect block;
    block.w = block_width;
    block.h = block_height;

    for(size_t x = 0; x < grid_width; x++) {
        for(size_t y = 0; y < grid_height; y++) {
            // create full-size grid block
            block.w = block_width;
            block.h = block_height;
            block.x = static_cast<int>(x) * block.w;
            block.y = static_cast<int>(y) * block.h;

            switch (grid2d.at(y * grid_width + x)) {
                case kWall:
                    SDL_SetRenderDrawColor(renderer, 0xAA, 0xAA, 0xAA, 0xFF);
                    SDL_RenderFillRect(renderer, &block);
                    break;
                case kPoint:
                    SDL_SetRenderDrawColor(renderer, 0xFF, 0xA5, 0x00, 0xFF);
                    ScaleRectangleInGrid(block, 0.1);
                    SDL_RenderFillRect(renderer, &block);
                    break;
                case kPower:
                    break;
                case kFruit:
                    break;
                case kEmpty:
                    break;
            }
        }
    }
}

void Map::ScaleRectangleInGrid(SDL_Rect &block, float scalingFactor){
    block.x = block.x + static_cast<int>((1 - scalingFactor) * 0.5 * block.w);
    block.y = block.y + static_cast<int>((1 - scalingFactor) * 0.5  * block.h);
    block.w = static_cast<int> (scalingFactor * block.w);
    block.h = static_cast<int> (scalingFactor * block.h);
}

/**
 * Returns a random x/y grid position where state != Map::StaticGameElement::kWall
 * @param constraintOnlyReachable: returns grid position where state == Map::StaticGameElement::kPoint
 * @return SDL_Point : struct containing x/y grid position
 */
SDL_Point Map::getRandomValidPosition(bool constraintOnlyReachable) {
    int x, y;

    while(true) {
        x = random_w(engine);
        y = random_h(engine);

        if (!constraintOnlyReachable){
            if (this->at(x, y) != StaticGameElement::kWall )
                break;
        } else {
            if (this->at(x, y) == StaticGameElement::kPoint )
                break;
        }

    }
    SDL_Point random_pos{x, y};

    return random_pos;
}
