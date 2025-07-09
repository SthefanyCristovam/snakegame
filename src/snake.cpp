#include "snake.h"
#include <stdlib.h>
#include <time.h>

void initSnake(Snake* snake) {
    snake->length = 3;
    snake->direction = DIR_RIGHT;
    snake->grow = 0;
    
    // Posição inicial no centro
    int startX = (LARGURA_JANELA/TAM_CELULA)/2;
    int startY = (ALTURA_JANELA/TAM_CELULA)/2;
    
    for(int i = 0; i < snake->length; i++) {
        snake->body[i].x = startX - i;
        snake->body[i].y = startY;
    }
}

void spawnFood(Food* food, const Snake* snake) {
    int valid = 0;
    while(!valid) {
        valid = 1;
        food->position.x = rand() % (LARGURA_JANELA/TAM_CELULA);
        food->position.y = rand() % (ALTURA_JANELA/TAM_CELULA);
        
        // Verifica se não está em cima da cobra
        for(int i = 0; i < snake->length; i++) {
            if(snake->body[i].x == food->position.x && 
               snake->body[i].y == food->position.y) {
                valid = 0;
                break;
            }
        }
    }
    food->active = 1;
    food->type = (rand() % 10) < 2 ? 1 : 0; // 20% chance de ser especial
}

void moveSnake(Snake* snake) {
    // Move cada segmento
    for(int i = snake->length-1; i > 0; i--) {
        snake->body[i] = snake->body[i-1];
    }
    
    // Move cabeça
    switch(snake->direction) {
        case DIR_UP:
            snake->body[0].y++;
            break;
        case DIR_RIGHT:
            snake->body[0].x++;
            break;
        case DIR_DOWN:
            snake->body[0].y--;
            break;
        case DIR_LEFT:
            snake->body[0].x--;
            break;
    }

    // Crescimento
    if (snake->grow > 0 && snake->length < MAX_TAMANHO) {
        snake->body[snake->length] = snake->body[snake->length - 1]; // duplica a última célula
        snake->length++;
        snake->grow--;
    }

}

void changeDirection(Snake* snake, Direction newDir) {
    // Previne movimento inverso imediato
    if((snake->direction == DIR_UP && newDir != DIR_DOWN) ||
       (snake->direction == DIR_DOWN && newDir != DIR_UP) ||
       (snake->direction == DIR_LEFT && newDir != DIR_RIGHT) ||
       (snake->direction == DIR_RIGHT && newDir != DIR_LEFT)) {
        snake->direction = newDir;
    }
}

int checkWallCollision(const Snake* snake) {
    return (snake->body[0].x < 0 || 
            snake->body[0].x >= LARGURA_JANELA/TAM_CELULA ||
            snake->body[0].y < 0 || 
            snake->body[0].y >= ALTURA_JANELA/TAM_CELULA);
}

int checkSelfCollision(const Snake* snake) {
    for(int i = 1; i < snake->length; i++) {
        if(snake->body[0].x == snake->body[i].x && 
           snake->body[0].y == snake->body[i].y) {
            return 1;
        }
    }
    return 0;
}

int checkFoodCollision(const Snake* snake, const Food* food) {
    return (food->active && 
            snake->body[0].x == food->position.x && 
            snake->body[0].y == food->position.y);
}