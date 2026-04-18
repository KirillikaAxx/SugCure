#include "Platform.hpp"
#include <vector>

Platform::Platform(int id, float x, float y, float w, float h): ID(id) {
    shape.setSize({ w, h });
    shape.setPosition({ x, y });
    shape.setFillColor(sf::Color::Green);
}

int Platform::getID() const {
    return ID;
}

sf::RectangleShape& Platform::getShape() {
    return shape; // edit
}

void Platform::remove(int ID, std::vector<Platform> &platforms) {
    platforms.erase(
        std::remove_if(platforms.begin(), platforms.end(),
            [&](const Platform& p) {
                return p.getID() == ID;
            }),
        platforms.end()
    );
}