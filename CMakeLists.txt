cmake_minimum_required(VERSION 3.20)
project(snakegame LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)

set(MSYS2_PATH "C:/msys64/mingw64")
include_directories(${MSYS2_PATH}/include)
link_directories(${MSYS2_PATH}/lib)

find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/snake.cpp
        src/game.cpp
        src/graphics.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        libfreeglut
        opengl32
        glu32
)