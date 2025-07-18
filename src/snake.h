#pragma once
#include <GL/freeglut.h>

#define WINDOW_WIDTH_SIZE 600
#define WINDOW_HEIGHT_SIZE 600
#define CELL_SIZE 20
#define MAX_SNAKE_SIZE 50

typedef enum {
    UP,
    RIGHT,
    DOWN,
    LEFT
} Direction;

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point body[MAX_SNAKE_SIZE];
    int length;
    Direction direction;
    int grow;
} Snake;

typedef struct {
    Point position;
    int active;
    int type; // 0=normal, 1=special
} Food;

// Initial configuration
void initSnake(Snake* snake);
void spawnFood(Food* food, const Snake* snake);

// Movement
void moveSnake(Snake* snake);
void changeDirection(Snake* snake, Direction newDir);

// Collision
int checkWallCollision(const Snake* snake);
int checkSelfCollision(const Snake* snake);
int checkFoodCollision(const Snake* snake, const Food* food);
