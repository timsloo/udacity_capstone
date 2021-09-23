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

