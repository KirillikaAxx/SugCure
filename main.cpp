#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

#include "Player.hpp"
#include "imgui.h"
#include "imgui-SFML.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE "SugCure"
#define STATIC_FPS 60


struct Platform {
    int ID;
    sf::RectangleShape shape;
};

Platform create(int ID, float x, float y, float w, float h) {
    Platform p;
    p.ID = ID;
    p.shape.setSize({ w, h });
    p.shape.setPosition({ x, y });
    p.shape.setFillColor(sf::Color::Green);
    p.ID = ID;
    return p;
}

void kill(int ID, std::vector<Platform>& array) {
    for (auto it = array.begin(); it != array.end();) {
        if (it->ID == ID)
            it = array.erase(it);
        else
            ++it;
    }
}

void drawBackground(sf::RenderWindow& window) {
    sf::RectangleShape tile(sf::Vector2f(32.f, 32.f));

    for (int y = 0; y < WINDOW_HEIGHT; y += 32) {
        for (int x = 0; x < WINDOW_WIDTH; x += 32) {
            if ((x / 32 + y / 32) % 2 == 0)
                tile.setFillColor(sf::Color(0, 105, 24));
            else
                tile.setFillColor(sf::Color(0, 181, 41));

            tile.setPosition((float)x, (float)y);
            window.draw(tile);
        }
    }
}

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

    platforms.push_back(create(1, 100, 600, 500, 20));

    while (window.isOpen()) {
        sf::Time dt = deltaClock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();
        }

        ImGui::SFML::Update(window, dt);

        std::vector<sf::RectangleShape> collisionShapes;
        collisionShapes.reserve(platforms.size());

        for (auto& p : platforms)
            collisionShapes.push_back(p.shape);

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

        if (ImGui::Button("Add platform")) {
            int ID = (int)platforms.size() + 1;
            platforms.push_back(create(ID, px, py, pw, ph));
        }

        ImGui::InputInt("ID", &pid);

        if (ImGui::Button("Remove by ID")) {
            kill(pid, platforms);
        }

        ImGui::End();

        window.clear(sf::Color::Black);

        for (auto& p : platforms)
            window.draw(p.shape);

        player.draw(window);

        ImGui::SFML::Render(window);

        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}