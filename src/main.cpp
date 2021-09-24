#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {
    constexpr std::size_t kFramesPerSecond{60};
    constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
    constexpr std::size_t kScreenWidth{640};
    constexpr std::size_t kScreenHeight{320};
    constexpr std::size_t kGridWidth{32};
    constexpr std::size_t kGridHeight{16};
    constexpr std::size_t kNumGhosts = 5;

    Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
    Controller controller;
    Map map(kGridWidth, kGridHeight, "../maps/standard_map.txt");
    Game game(kGridWidth, kGridHeight, kNumGhosts, std::move(map));
    game.Run(controller, renderer, kMsPerFrame);
    std::cout << "Final score: " <<  game.GetScore() << "\n";
    std::cout << "Game has terminated successfully!\n";
    return 0;
}