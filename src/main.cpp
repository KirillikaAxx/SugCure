#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

#include "Player.hpp"
#include "Platform.hpp"
#include "MapManager.hpp"
#include "Editor/Editor.h"
#include "config.h"

#include "imgui.h"
#include "imgui-SFML.h"

int main() {
    sf::RenderWindow window(
        sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
        WINDOW_TITLE
    );

    window.setFramerateLimit(STATIC_FPS);

    ImGui::SFML::Init(window);

    Player player;
    std::vector<Platform> platforms;

    platforms.emplace_back(1, 100.f, 600.f, 500.f, 20.f);

    sf::Clock deltaClock;

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time dt = deltaClock.restart();

        ImGui::SFML::Update(window, dt);

        std::vector<sf::RectangleShape> collisionShapes;
        collisionShapes.reserve(platforms.size());

        for (auto& p : platforms)
            collisionShapes.push_back(p.getShape());

        player.update(collisionShapes);

        // editor is here
        Editor::edit(platforms, player, dt);

        window.clear(sf::Color::Black);

        for (auto& p : platforms)
            window.draw(p.getShape());

        player.draw(window);

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}