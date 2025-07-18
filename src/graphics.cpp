#include "graphics.h"
#include <GL/freeglut.h>
#include <stdio.h>

static float baseHeight = WINDOW_HEIGHT_SIZE / 4 * 3;
static float baseWidth = WINDOW_WIDTH_SIZE / 2;

static void drawCell(int x, int y, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
        glVertex2i(x * CELL_SIZE, y * CELL_SIZE);
        glVertex2i((x + 1) * CELL_SIZE, y * CELL_SIZE);
        glVertex2i((x + 1) * CELL_SIZE, (y + 1) * CELL_SIZE);
        glVertex2i(x * CELL_SIZE, (y + 1) * CELL_SIZE);
    glEnd();
}

void drawTextCustomAxis(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    for(const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void drawTextWCentralized(const char* text, float height_offset) {
    int stringWidth = 0;
    for (const char* c = text; *c != '\0'; ++c) {
        stringWidth += glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, *c);
    }

    glRasterPos2f(baseWidth - (stringWidth/2), baseHeight - height_offset);
    for(const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void drawText(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    for(const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void drawGame(const Game* game) {
    // Background
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Environment
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_LINES);
    for(int i = 0; i <= WINDOW_WIDTH_SIZE; i += CELL_SIZE) {
        glVertex2i(i, 0);
        glVertex2i(i, WINDOW_HEIGHT_SIZE);
    }
    for(int j = 0; j <= WINDOW_HEIGHT_SIZE; j += CELL_SIZE) {
        glVertex2i(0, j);
        glVertex2i(WINDOW_WIDTH_SIZE, j);
    }
    glEnd();

    // Snake
    for(int i = 0; i < game->snake.length; i++) {
        float intensity = 0.5f + 0.5f * (i / (float)game->snake.length);
        drawCell(game->snake.body[i].x, game->snake.body[i].y,
                0.0f, intensity, 0.0f);
    }

    // Food
    if(game->food.active) {
        if(game->food.type == 0) {
            drawCell(game->food.position.x, game->food.position.y, 1.0f, 0.0f, 0.0f);
        } else {
            drawCell(game->food.position.x, game->food.position.y, 1.0f, 1.0f, 0.0f);
        }
    }

    drawHUD(game);
}

void drawMenu() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Background
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f); // Dark blue
    glClear(GL_COLOR_BUFFER_BIT);

    // Title
    glColor3f(0.0f, 1.0f, 0.0f); // Green
    drawTextWCentralized("SNAKE GAME", 0);

    // Instructions
    glColor3f(1.0f, 1.0f, 1.0f); // White
    drawTextWCentralized("Use your arrows to move", 40);
    drawTextWCentralized("Press SPACE to begin", 120);
    drawTextWCentralized("Press ESC to pause", 150);
}

void drawGameOver(const Game* game) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Background
    glClearColor(0.2f, 0.1f, 0.1f, 1.0f); // dark read
    glClear(GL_COLOR_BUFFER_BIT);

    // Title
    glColor3f(1.0f, 0.0f, 0.0f); // red
    drawTextCustomAxis(WINDOW_WIDTH_SIZE/2 - 70, WINDOW_HEIGHT_SIZE/2 + 60, "GAME OVER");

    // Scores
    char scoreText[50];
    sprintf(scoreText, "Current score: %d", game->score);
    glColor3f(1.0f, 1.0f, 1.0f); // Branco
    drawTextCustomAxis(WINDOW_WIDTH_SIZE/2 - 50, WINDOW_HEIGHT_SIZE/2 + 20, scoreText);

    // High score
    char highScoreText[50];
    sprintf(highScoreText, "Record: %d", game->highestScore);
    drawTextCustomAxis(WINDOW_WIDTH_SIZE/2 - 50, WINDOW_HEIGHT_SIZE/2 - 10, highScoreText);

    // Options
    drawTextCustomAxis(WINDOW_WIDTH_SIZE/2 - 120, WINDOW_HEIGHT_SIZE/2 - 50, "Press R to reload");
    drawTextCustomAxis(WINDOW_WIDTH_SIZE/2 - 100, WINDOW_HEIGHT_SIZE/2 - 80, "Press ESC to leave =(");

}

void drawHUD(const Game* game) {
    char scoreText[50];
    sprintf(scoreText, "Score: %d", game->score);

    char levelText[50];
    sprintf(levelText, "Level: %d", game->level);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawText(10, WINDOW_HEIGHT_SIZE - 20, scoreText);
    drawText(WINDOW_WIDTH_SIZE - 100, WINDOW_HEIGHT_SIZE - 20, levelText);
}