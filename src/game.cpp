#include "game.h"
#include <stdlib.h>
#include <time.h>

void initGame(Game* game) {
    srand(time(NULL));
    game->state = GAME_MENU;
    game->score = 0;
    game->highScore = 0;
    game->speed = 150;
    game->level = 1;
    initSnake(&game->snake);
    spawnFood(&game->food, &game->snake);
}

void updateGame(Game* game) {
    if(game->state != GAME_PLAYING) return;

    moveSnake(&game->snake);

    // Verifica colisões - CORREÇÃO AQUI
    if(checkWallCollision(&game->snake)) {
        game->state = GAME_OVER;
        return;
    }

    if(checkSelfCollision(&game->snake)) {
        game->state = GAME_OVER;
        return;
    }

    // Verifica comida
    if(checkFoodCollision(&game->snake, &game->food)) {
        game->score += (game->food.type == 0) ? 1 : 5;
        if(game->score > game->highScore) {
            game->highScore = game->score;
        }

        game->snake.grow += (game->food.type == 0) ? 1 : 3;
        spawnFood(&game->food, &game->snake);

        if(game->score % 5 == 0) {
            game->level++;
            game->speed = (game->speed > 50) ? game->speed - 10 : 50;
        }
    }
}

void handleInput(Game* game, unsigned char key, int x, int y) {
    switch(key) {
        case 27: // ESC
            if(game->state == GAME_PLAYING) {
                game->state = GAME_PAUSED;
            } else if(game->state == GAME_PAUSED) {
                game->state = GAME_PLAYING;
            } else if(game->state == GAME_OVER) {
                exit(0); // Sair do jogo
            }
            break;
        case 'r':
        case 'R':
            if(game->state == GAME_OVER) {
                initGame(game);
                game->state = GAME_PLAYING;
            }
            break;
        case ' ':
            if(game->state == GAME_MENU) {
                game->state = GAME_PLAYING;
            }
            break;
    }
}

void handleSpecialInput(Game* game, int key, int x, int y) {
    if(game->state != GAME_PLAYING) return;

    switch(key) {
        case GLUT_KEY_UP:
            changeDirection(&game->snake, DIR_UP);
            break;
        case GLUT_KEY_RIGHT:
            changeDirection(&game->snake, DIR_RIGHT);
            break;
        case GLUT_KEY_DOWN:
            changeDirection(&game->snake, DIR_DOWN);
            break;
        case GLUT_KEY_LEFT:
            changeDirection(&game->snake, DIR_LEFT);
            break;
    }
}