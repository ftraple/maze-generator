#ifndef INCLUDE_MAZE_H_
#define INCLUDE_MAZE_H_

#include <SFML/Graphics.hpp>
#include <stack>
#include <vector>
#include <cstdlib>
#include <optional>
#include <iostream>

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
    std::vector<std::vector<Cell>> m_data;

    bool is_generated{false};
    int m_x{0};
    int m_y{0};
    Cell* m_current{nullptr};
    std::stack<std::pair<int, int>> m_path;

    void generate();

    std::optional<std::pair<int, int>> choose_next_cell();
};

#endif // INCLUDE_MAZE_H_
