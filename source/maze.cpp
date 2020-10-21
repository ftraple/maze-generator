#include "maze.h"

Maze::Maze(int width, int height, int cell_size, int start_x, int start_y)
    : m_width{width}, m_height{height}, m_cell_resolution{cell_size},
      m_position{start_x, start_y}, m_data(width, std::vector<Cell>(height)) {

    m_current = &m_data[m_position.x][m_position.y];
    m_current->visited = true;
    m_path.push(m_position);
}

void Maze::update() {
    if (!is_generated) generate();
}

void Maze::generate() {
    auto position = Maze::choose_next_cell();
    if (position) {
        Cell *next = &m_data[position->x][position->y];
        next->visited = true;
        // Remove walls
        if (m_position.x > position->x) {
            m_current->left = false;
            next->right = false;
        }
        if (m_position.x < position->x) {
            m_current->right = false;
            next->left = false;
        }
        if (m_position.y > position->y) {
            m_current->top = false;
            next->botton = false;
        }
        if (m_position.y < position->y) {
            m_current->botton = false;
            next->top = false;
        }
        // Set next cell as the current
        m_position = *position;
        m_current = next;
        m_path.push(m_position);
    } else {
        if (!m_path.empty()) {
            auto position = m_path.top();
            m_position.x = position.x;
            m_position.y = position.y;
            m_current = &m_data[m_position.x][m_position.y];
            m_path.pop();
        }
    }
}

std::optional<sf::Vector2i> Maze::choose_next_cell() {
    std::vector<sf::Vector2i> next_cell_list;
    // Check left
    if (m_position.x - 1 >= 0) {
        if (!m_data[m_position.x - 1][m_position.y].visited) {
            next_cell_list.push_back({m_position.x - 1, m_position.y});
        }
    }
    // Check right
    if (m_position.x + 1 < m_width) {
        if (!m_data[m_position.x + 1][m_position.y].visited) {
            next_cell_list.push_back({m_position.x + 1, m_position.y});
        }
    }
    // Check top
    if (m_position.y - 1 >= 0) {
        if (!m_data[m_position.x][m_position.y - 1].visited) {
            next_cell_list.push_back({m_position.x, m_position.y - 1});
        }
    }
    // Check botton
    if (m_position.y + 1 < m_height) {
        if (!m_data[m_position.x][m_position.y + 1].visited) {
            next_cell_list.push_back({m_position.x, m_position.y + 1});
        }
    }
    // Selected next cell
    if (next_cell_list.size() > 0) {
        int index = std::rand() % next_cell_list.size();
        return next_cell_list[index];
    }
    return std::nullopt;
}

void Maze::draw(sf::RenderWindow &window) {
    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            int gx = x * m_cell_resolution;
            int gy = y * m_cell_resolution;
            Cell *cell = &m_data[x][y];
            if (cell == m_current) {
                sf::RectangleShape rectangle;
                rectangle.setFillColor(sf::Color::Green);
                rectangle.setSize(sf::Vector2f(m_cell_resolution - 4, m_cell_resolution - 4));
                rectangle.setPosition(gx + 1, gy + 1);
                window.draw(rectangle);
            } else {
                if (!cell->visited) {
                    sf::RectangleShape rectangle;
                    rectangle.setFillColor(sf::Color{196, 196, 196, 255});
                    rectangle.setSize(sf::Vector2f(m_cell_resolution - 4, m_cell_resolution - 4));
                    rectangle.setPosition(gx + 2, gy + 2);
                    window.draw(rectangle);
                }
            }
            if (cell->top) {
                sf::RectangleShape rectangle;
                rectangle.setFillColor(sf::Color::White);
                rectangle.setSize(sf::Vector2f(m_cell_resolution, 1));
                rectangle.setPosition(gx, gy);
                window.draw(rectangle);
            }
            if (cell->botton) {
                sf::RectangleShape rectangle;
                rectangle.setFillColor(sf::Color::White);
                rectangle.setSize(sf::Vector2f(m_cell_resolution, 1));
                rectangle.setPosition(gx, gy + m_cell_resolution - 1);
                window.draw(rectangle);
            }
            if (cell->left) {
                sf::RectangleShape rectangle;
                rectangle.setFillColor(sf::Color::White);
                rectangle.setSize(sf::Vector2f(1, m_cell_resolution));
                rectangle.setPosition(gx, gy);
                window.draw(rectangle);
            }
            if (cell->right) {
                sf::RectangleShape rectangle;
                rectangle.setFillColor(sf::Color::White);
                rectangle.setSize(sf::Vector2f(1, m_cell_resolution));
                rectangle.setPosition(gx + m_cell_resolution - 1, gy);
                window.draw(rectangle);
            }
        }
    }
}
