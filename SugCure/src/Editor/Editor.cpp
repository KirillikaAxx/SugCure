//
// Created by Kirill on 19.04.2026.
//

#include "Editor.h"

#include <iostream>
#include <imgui.h>

#include "Player.hpp"
#include "Platform.hpp"
#include "MapManager.hpp"

void Editor::edit(std::vector<Platform>& platforms,
                  Player& player,
                  const sf::Time& dt)
{
    ImGui::Begin("SugCure Editor");

    ImGui::Text("FPS: %.1f", 1.f / dt.asSeconds());

    auto pos = player.getPosition();
    ImGui::Text("Player X: %.1f", pos.x);
    ImGui::Text("Player Y: %.1f", pos.y);

    if (ImGui::Button("Return player")) {
        player.returnOnBase();
    }

    ImGui::Separator();
    ImGui::Text("Level Editor");

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
        int id = static_cast<int>(platforms.size()) + 1;
        platforms.emplace_back(id, px, py, pw, ph);
    }

    ImGui::InputInt("ID", &pid);

    if (ImGui::Button("Remove by ID")) {
        Platform::remove(pid, platforms);
    }

    static char mapName[255] = "";
    static char mapToLoadName[255] = "";

    ImGui::Separator();
    ImGui::Text("Map Tools");

    ImGui::InputText("Save name", mapName, 255);
    if (ImGui::Button("Save")) {
        int code = MapManager::saveMap(platforms, mapName);
        std::cout << "Save result: " << code << std::endl;
    }

    ImGui::InputText("Load name", mapToLoadName, 255);
    if (ImGui::Button("Load")) {
        int code = MapManager::loadMap(platforms, mapToLoadName);
        std::cout << "Load result: " << code << std::endl;
    }

    ImGui::End();
}