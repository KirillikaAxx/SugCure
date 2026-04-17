#include "Player.hpp"

Player::Player() {
    texture.loadFromFile("assets/img/New Piskel.png");
    sprite.setTexture(texture);

    sf::Vector2u size = texture.getSize();
    sprite.setScale(32.f / size.x, 32.f / size.y);

    width = 32.f;
    height = 32.f;

    x = 100.f;
    y = 300.f;

    velocityX = 0.f;
    velocityY = 0.f;

    speed = 4.f;
    gravity = 0.5f;
    jumpForce = -10.f;

    onGround = false;

    sprite.setPosition(x, y);
}

void Player::jump() {
    velocityY = jumpForce;
    onGround = false;
}

void Player::update(const std::vector<sf::RectangleShape>& platforms) {
    velocityX = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        velocityX = -speed;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        velocityX = speed;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && onGround)
        jump();

    velocityY += gravity;

    x += velocityX;

    sf::FloatRect playerBoundsX(x, y, width, height);

    for (const auto& p : platforms) {
        sf::FloatRect b = p.getGlobalBounds();

        if (playerBoundsX.intersects(b)) {
            if (velocityX > 0)
                x = b.left - width;
            else if (velocityX < 0)
                x = b.left + b.width;

            velocityX = 0.f;
            playerBoundsX.left = x;
        }
    }

    y += velocityY;

    sf::FloatRect playerBoundsY(x, y, width, height);
    onGround = false;

    for (const auto& p : platforms) {
        sf::FloatRect b = p.getGlobalBounds();

        if (playerBoundsY.intersects(b)) {
            if (velocityY > 0) {
                y = b.top - height;
                onGround = true;
            }
            else if (velocityY < 0) {
                y = b.top + b.height;
            }

            velocityY = 0.f;
            playerBoundsY.top = y;
        }
    }

    sprite.setPosition(x, y);
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Player::returnOnBase() {
    x = 100;
    y = 300;
}

sf::Vector2f Player::getPosition() const {
    return { x, y };
}