#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

const int GRID_W = 10;
const int GRID_H = 10;
const int CELL_SIZE = 40;



int main() {
    sf::RenderWindow window(sf::VideoMode({GRID_W * CELL_SIZE, GRID_H * CELL_SIZE}),
                            "2D Grid World (SFML 3.0.2)");

    // Player position
    int playerX = 0, playerY = 0;

    // Obstacles
    std::vector<std::pair<int, int>> obstacles = {
        {3, 3}, {3, 4}, {4, 4}, {6, 7}
    };

    std::cout << "start" << std::endl;
    while (window.isOpen()) {
        // --- Event handling ---
        while (true) {
            auto optEvent = window.pollEvent();
            if (!optEvent)
                break;

            const auto& event = *optEvent;
            if (event.is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // --- Movement ---
        int newX = playerX;
        int newY = playerY;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) newY--;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) newY++;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) newX--;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) newX++;

        // Stay inside grid
        if (newX >= 0 && newX < GRID_W && newY >= 0 && newY < GRID_H) {
            bool blocked = false;
            for (auto [ox, oy] : obstacles) {
                if (ox == newX && oy == newY)
                    blocked = true;
            }
            if (!blocked) {
                playerX = newX;
                playerY = newY;
            }
        }

        // --- Drawing ---
        window.clear(sf::Color::White);

        // Draw grid
        sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 2, CELL_SIZE - 2));
        for (int i = 0; i < GRID_W; i++) {
            for (int j = 0; j < GRID_H; j++) {
                cell.setPosition(sf::Vector2f(i * CELL_SIZE, j * CELL_SIZE));
                cell.setFillColor(sf::Color(230, 230, 230));
                window.draw(cell);
            }
        }

        // Draw obstacles
        cell.setFillColor(sf::Color::Black);
        for (auto [x, y] : obstacles) {
            cell.setPosition(sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE));
            window.draw(cell);
        }

        // Draw player
        sf::RectangleShape player(sf::Vector2f(CELL_SIZE - 4, CELL_SIZE - 4));
        player.setPosition(sf::Vector2f(playerX * CELL_SIZE + 2, playerY * CELL_SIZE + 2));
        player.setFillColor(sf::Color::Green);
        window.draw(player);

        window.display();
    }

    return 0;
}