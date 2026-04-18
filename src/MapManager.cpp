#include "MapManager.hpp"
#include "config.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>

int MapManager::saveMap(const std::vector<Platform>& platforms, const std::string& fileName) {
    std::ofstream file(fileName);

    if (!file.is_open())
        return -1;

    for (const auto& p : platforms) {
        sf::Vector2f pos = p.getShape().getPosition();
        sf::Vector2f size = p.getShape().getSize();

        std::string type = "rect";
        int ID = p.getID();

        float x = pos.x;
        float y = pos.y;
        float w = size.x;
        float h = size.y;

        file << type << " "
             << x << " "
             << y << " "
             << w << " "
             << h << " "
             << ID << "\n";
    }

    return 0;
}

int MapManager::loadMap(std::vector<Platform>& platforms, const std::string& fileName) {
    std::ifstream file(fileName);

    if (!std::filesystem::exists(fileName)) {
    #ifdef DEBUG
        std::cout << "File does not exist: " << fileName << std::endl;
    #endif
        return -1;
    }
    if (!file.is_open())
        return -1;

    platforms.clear();

    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);

        std::string type;
        float x, y, w, h;
        int id;

        if (!(iss >> type >> x >> y >> w >> h >> id))
            continue;

        platforms.emplace_back(id, x, y, w, h);
    }

    return 0;
}