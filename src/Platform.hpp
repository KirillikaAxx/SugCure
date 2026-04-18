#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Platform {
public:
    Platform(int ID, float x, float y, float w, float h);

    int getID() const;
    const sf::RectangleShape& Platform::getShape() const;
    static void remove(int ID, std::vector<Platform> &platforms);

private:
    int ID;
    sf::RectangleShape shape;
};