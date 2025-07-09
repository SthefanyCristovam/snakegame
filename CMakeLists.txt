cmake_minimum_required(VERSION 3.20)
project(jogodacobrinha LANGUAGES CXX)  # Mude para CXX
set(CMAKE_CXX_STANDARD 11)            # Em vez de C_STANDARD

# Configurações para Windows - Aumenta tamanho da stack
if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,8388608")
endif()

# Configurações para MSYS2/MinGW
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
        winmm
        gdi32
)

# Copiar DLLs necessárias
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${MSYS2_PATH}/bin/libfreeglut.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMAND ${CMAKE_COMMAND} -E copy
        "${MSYS2_PATH}/bin/libgcc_s_seh-1.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMAND ${CMAKE_COMMAND} -E copy
        "${MSYS2_PATH}/bin/libstdc++-6.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)