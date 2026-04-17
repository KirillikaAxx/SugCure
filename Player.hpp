#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Player {
private:
    sf::Texture texture;
    sf::Sprite sprite;

    float x, y;
    float velocityX, velocityY;

    float speed;
    float gravity;
    float jumpForce;

    float width;
    float height;

    bool onGround;

public:
    Player();

    void returnOnBase();
    void update(const std::vector<sf::RectangleShape>& platforms);
    void jump();
    void draw(sf::RenderWindow& window);

    sf::Vector2f getPosition() const;
};