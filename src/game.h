#pragma once
#include "snake.h"

typedef enum {
    GAME_MENU,
    GAME_PLAYING,
    GAME_OVER,
    GAME_PAUSED
} GameState;

typedef struct {
    Snake snake;
    Food food;
    GameState state;
    int score;
    int highestScore;
    int speed;
    int level;
} Game;

void initGame(Game* game);
void updateGame(Game* game);
void handleInput(Game* game, unsigned char key, int x, int y);
void handleSpecialInput(Game* game, int key, int x, int y);
