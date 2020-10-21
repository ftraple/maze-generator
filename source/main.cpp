#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <thread>

#include "maze.h"

int main(int argc, char **argv) {
   
    std::srand(std::time(nullptr));

    sf::RenderWindow window(sf::VideoMode(640, 480), "Maze Generator");

    Maze maze(16, 12, 40, 0, 0);

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds{100});
        window.clear();
        maze.update();
        maze.draw(window);
        window.display();
    }

    return EXIT_SUCCESS;
}
