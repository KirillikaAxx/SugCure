#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <algorithm> // std::remove_if

#include "Player.hpp"
#include "Platform.hpp"
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

    sf::Clock deltaClock;

    // old: platforms.push_back(Platform::create(...));
    // new: emplace_back constructor
    platforms.emplace_back(1, 100.f, 600.f, 500.f, 20.f);

    while (window.isOpen()) {
        sf::Time dt = deltaClock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();
        }

        ImGui::SFML::Update(window, dt);

        // old: copy shapes into vector<RectangleShape>
        // new: still needed unless Player API changes later
        std::vector<sf::RectangleShape> collisionShapes;
        collisionShapes.reserve(platforms.size());

        for (auto& p : platforms)
            collisionShapes.push_back(p.getShape()); // old: p.shape

        player.update(collisionShapes);

        ImGui::Begin("SugCure Debug");

        ImGui::Text("SugCure Debug");
        ImGui::Separator();

        ImGui::Text("FPS: %.1f", 1.f / dt.asSeconds());

        sf::Vector2f pos = player.getPosition();
        ImGui::Text("Player X: %.1f", pos.x);
        ImGui::Text("Player Y: %.1f", pos.y);

        if (ImGui::Button("Return player")) {
            player.returnOnBase();
        }

        ImGui::Separator();
        ImGui::Text("Level Editor");
        ImGui::Separator();

        static float px = 100.f;
        static float py = 100.f;
        static float pw = 200.f;
        static float ph = 20.f;
        static int pid = 0;

        ImGui::InputFloat("X", &px);
        ImGui::InputFloat("Y", &py);
        ImGui::InputFloat("Width", &pw);
        ImGui::InputFloat("Height", &ph);

        // old:
        // int ID = (int)platforms.size() + 1;
        // platforms.push_back(Platform::create(...));

        // new:
        if (ImGui::Button("Add platform")) {
            int ID = (int)platforms.size() + 1;
            platforms.emplace_back(ID, px, py, pw, ph);
        }

        ImGui::InputInt("ID", &pid);

        if (ImGui::Button("Remove by ID")) {
            //platforms.erase(
            //    std::remove_if(platforms.begin(), platforms.end(),
            //        [&](const Platform& p) {
            //            return p.getID() == pid;
            //        }),
            //    platforms.end()
            //);
            Platform::remove(pid, platforms);
        }

        ImGui::End();

        window.clear(sf::Color::Black);

        // old: window.draw(p.shape)
        // new: getter
        for (auto& p : platforms)
            window.draw(p.getShape());

        player.draw(window);

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}