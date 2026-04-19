# fixed CMakeLists.txt version

cmake_minimum_required(VERSION 3.20)
project(SugCure)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------------------------
# MSVC build boost
# ---------------------------
if (MSVC)
    add_compile_options(/MP)
endif()

# ---------------------------
# SFML
# ---------------------------
set(SFML_DIR "${CMAKE_SOURCE_DIR}/libraries/lib/cmake/SFML")
find_package(SFML REQUIRED COMPONENTS graphics window system audio network)

# ---------------------------
# ImGui
# ---------------------------
add_library(imgui STATIC
        libraries/include/imgui/imgui.cpp
        libraries/include/imgui/imgui_draw.cpp
        libraries/include/imgui/imgui_tables.cpp
        libraries/include/imgui/imgui_widgets.cpp
        libraries/include/imgui/imgui-SFML.cpp
)

target_include_directories(imgui PRIVATE
        ${CMAKE_SOURCE_DIR}/libraries/include
        ${CMAKE_SOURCE_DIR}/libraries/include/imgui
)

target_link_libraries(imgui PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
        opengl32
)

# ---------------------------
# Game sources
# ---------------------------
set(SOURCES
        src/main.cpp
        src/Player.cpp
        src/Platform.cpp
        src/MapManager.cpp
        src/Editor/Editor.cpp
        src/Editor/Editor.h
)

add_executable(SugCure ${SOURCES})

# ---------------------------
# Includes
# ---------------------------
target_include_directories(SugCure PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/libraries/include
        ${CMAKE_SOURCE_DIR}/libraries/include/imgui
)

# ---------------------------
# Linking
# ---------------------------
target_link_libraries(SugCure PRIVATE
        imgui
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
        sfml-network
        opengl32
)

# ---------------------------
# Copy assets after build
# ---------------------------
add_custom_command(TARGET SugCure POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:SugCure>/assets
)