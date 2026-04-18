cmake_minimum_required(VERSION 3.20)
project(SugCure)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------------------------
# SFML
# ---------------------------
set(SFML_DIR "${CMAKE_SOURCE_DIR}/libraries/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML REQUIRED COMPONENTS graphics window system audio network)

# ---------------------------
# ImGui sources
# ---------------------------
set(IMGUI_SRC
        libraries/include/imgui/imgui.cpp
        libraries/include/imgui/imgui_draw.cpp
        libraries/include/imgui/imgui_tables.cpp
        libraries/include/imgui/imgui_widgets.cpp
        libraries/include/imgui/imgui-SFML.cpp
)

# ---------------------------
# Source files
# ---------------------------
set(SOURCES
        src/main.cpp
        src/Player.cpp
        src/Platform.cpp
        src/MapManager.cpp
        ${IMGUI_SRC}
)

add_executable(SugCure ${SOURCES})

# ---------------------------
# Include dirs
# ---------------------------
target_include_directories(SugCure PRIVATE
        ${CMAKE_SOURCE_DIR}/libraries/include
        ${CMAKE_SOURCE_DIR}/libraries/include/imgui
        ${CMAKE_SOURCE_DIR}/src
)

# ---------------------------
# Linking
# ---------------------------
target_link_libraries(SugCure
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
        sfml-network
        opengl32
)

# ---------------------------
# Assets copy
# ---------------------------
add_custom_command(TARGET SugCure POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:SugCure>/assets
)

# ---------------------------
# DLL copy
# ---------------------------
add_custom_command(TARGET SugCure POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/out
        $<TARGET_FILE_DIR:SugCure>
)