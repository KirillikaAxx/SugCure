#pragma once

#include <vector>
#include <SFML/System.hpp>

class Player;
class Platform;

class Editor {
public:
    static void edit(std::vector<Platform>& platforms,
                     Player& player,
                     const sf::Time& dt);
};