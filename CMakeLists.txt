cmake_minimum_required(VERSION 3.20)
project(SugCure)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------------------------------------------------
# OUTPUT
# -------------------------------------------------
set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/out)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${OUTPUT_DIR})

# -------------------------------------------------
# FULL STATIC RUNTIME
# -------------------------------------------------
set(CMAKE_EXE_LINKER_FLAGS
        "-static -static-libgcc -static-libstdc++"
)

# -------------------------------------------------
# SFML
# -------------------------------------------------
set(SFML_DIR "${CMAKE_SOURCE_DIR}/libraries/lib/cmake/SFML")
find_package(SFML REQUIRED COMPONENTS graphics window system audio)

# -------------------------------------------------
# ImGui
# -------------------------------------------------
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

# -------------------------------------------------
# GAME
# -------------------------------------------------
set(SOURCES
        src/main.cpp
        src/Player.cpp
        src/Platform.cpp
        src/MapManager.cpp
        src/Editor/Editor.cpp
)

add_executable(SugCure ${SOURCES})

target_include_directories(SugCure PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/libraries/include
        ${CMAKE_SOURCE_DIR}/libraries/include/imgui
)

target_link_libraries(SugCure PRIVATE
        imgui
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
        opengl32
)

# -------------------------------------------------
# ASSETS ONLY
# -------------------------------------------------
add_custom_command(TARGET SugCure POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${OUTPUT_DIR}/assets
)