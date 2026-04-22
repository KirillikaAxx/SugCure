#pragma once

#include "Platform.hpp"
#include <string>
#include <vector>

class MapManager {
public:
	static int saveMap(const std::vector<Platform>& platforms, const std::string& fileName);
	static int loadMap(std::vector<Platform>& platforms, const std::string& fileName);
};

