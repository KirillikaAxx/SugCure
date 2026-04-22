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

    sf::SoundBuffer buffer;
    buffer.loadFromFile("assets/snd/jump.mp3");

    sf::Sound sound;
    sound.setBuffer(buffer);

    bool showJumpEffect = false;
    sf::Clock effectClock;

    sf::RectangleShape jumpShapeEffect;
    float jumpEffectAlpha = 20;
    jumpShapeEffect.setFillColor(sf::Color(255, 157, 0, jumpEffectAlpha));
    jumpShapeEffect.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    jumpShapeEffect.setPosition(0, 0);


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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            if (player.jump()) {
                sound.stop();
                sound.play();

                showJumpEffect = true;
                effectClock.restart();
                jumpEffectAlpha = 20;
            }
        }

        player.update(collisionShapes);

        Editor::edit(platforms, player, dt);

        window.clear(sf::Color::Black);

        if (showJumpEffect) {
            float t = effectClock.getElapsedTime().asSeconds();

            float duration = 3.f;

            float progress = t / duration; // 0 -> 1

            jumpEffectAlpha = 20.f * (1.f - progress);

            if (jumpEffectAlpha < 0.f)
                jumpEffectAlpha = 0.f;

            jumpShapeEffect.setFillColor(
                sf::Color(255, 157, 0, static_cast<sf::Uint8>(jumpEffectAlpha))
            );

            window.draw(jumpShapeEffect);

            if (t >= duration)
                showJumpEffect = false;
        }

        for (auto& p : platforms)
            window.draw(p.getShape());

        player.draw(window);

        ImGui::SFML::Render(window);
        window.display();
    }
}