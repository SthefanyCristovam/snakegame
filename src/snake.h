#ifndef SNAKE_H
#define SNAKE_H

#include <GL/freeglut.h>

#define LARGURA_JANELA 600
#define ALTURA_JANELA 600
#define TAM_CELULA 20
#define MAX_TAMANHO 50

typedef enum {
    DIR_UP,
    DIR_RIGHT,
    DIR_DOWN,
    DIR_LEFT
} Direction;

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point body[MAX_TAMANHO];
    int length;
    Direction direction;
    int grow;
} Snake;

typedef struct {
    Point position;
    int active;
    int type; // 0=normal, 1=especial
} Food;

// Inicialização
void initSnake(Snake* snake);
void spawnFood(Food* food, const Snake* snake);

// Movimento
void moveSnake(Snake* snake);
void changeDirection(Snake* snake, Direction newDir);

// Colisão
int checkWallCollision(const Snake* snake);
int checkSelfCollision(const Snake* snake);
int checkFoodCollision(const Snake* snake, const Food* food);

#endif