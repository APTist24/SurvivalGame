#include <iostream>
#include <memory>
#include "core/Engine.h"

int main(int argc, char* argv[]) {
    std::cout << "Starting Survival Roguelike Game..." << std::endl;

    try {
        auto engine = std::make_unique<Engine>();
        engine->Init();
        engine->Run();
        engine->Shutdown();
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Game exited successfully." << std::endl;
    return EXIT_SUCCESS;
}