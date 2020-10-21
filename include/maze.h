#ifndef INCLUDE_MAZE_H_
#define INCLUDE_MAZE_H_

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <optional>
#include <stack>
#include <vector>

class Maze {
public:
    Maze(int width, int height, int cell_size, int start_x, int start_y);

    void update();

    void draw(sf::RenderWindow &window);

private:
    struct Cell {
        bool visited{false};
        bool top{true};
        bool botton{true};
        bool left{true};
        bool right{true};
    };

    int m_width;
    int m_height;
    int m_cell_resolution;
    sf::Vector2i m_position{0, 0};
    std::vector<std::vector<Cell>> m_data;
    bool is_generated{false};
    Cell *m_current{nullptr};
    std::stack<sf::Vector2i> m_path;

    void generate();

    std::optional<sf::Vector2i> choose_next_cell();
};

#endif // INCLUDE_MAZE_H_
