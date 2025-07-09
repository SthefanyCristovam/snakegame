#include "graphics.h"
#include <GL/freeglut.h>
#include <stdio.h>

static void drawCell(int x, int y, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
        glVertex2i(x * TAM_CELULA, y * TAM_CELULA);
        glVertex2i((x + 1) * TAM_CELULA, y * TAM_CELULA);
        glVertex2i((x + 1) * TAM_CELULA, (y + 1) * TAM_CELULA);
        glVertex2i(x * TAM_CELULA, (y + 1) * TAM_CELULA);
    glEnd();
}

void drawText(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    for(const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void drawGame(const Game* game) {
    // Fundo
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Grade
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_LINES);
    for(int i = 0; i <= LARGURA_JANELA; i += TAM_CELULA) {
        glVertex2i(i, 0);
        glVertex2i(i, ALTURA_JANELA);
    }
    for(int j = 0; j <= ALTURA_JANELA; j += TAM_CELULA) {
        glVertex2i(0, j);
        glVertex2i(LARGURA_JANELA, j);
    }
    glEnd();

    // Cobra
    for(int i = 0; i < game->snake.length; i++) {
        float intensity = 0.5f + 0.5f * (i / (float)game->snake.length);
        drawCell(game->snake.body[i].x, game->snake.body[i].y,
                0.0f, intensity, 0.0f);
    }

    // Comida
    if(game->food.active) {
        if(game->food.type == 0) {
            drawCell(game->food.position.x, game->food.position.y, 1.0f, 0.0f, 0.0f);
        } else {
            drawCell(game->food.position.x, game->food.position.y, 1.0f, 1.0f, 0.0f);
        }
    }

    // HUD
    drawHUD(game);

    //glutSwapBuffers();
}

void drawMenu() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Fundo colorido
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Título do jogo
    glColor3f(0.0f, 1.0f, 0.0f); // Verde
    drawText(LARGURA_JANELA/2 - 120, ALTURA_JANELA/2 + 40, "JOGO DA COBRINHA");

    // Instruções
    glColor3f(1.0f, 1.0f, 1.0f); // Branco
    drawText(LARGURA_JANELA/2 - 100, ALTURA_JANELA/2, "Pressione ESPACO para comecar");

    // Controles
    drawText(LARGURA_JANELA/2 - 120, ALTURA_JANELA/2 - 30, "Use as setas para mover");
    drawText(LARGURA_JANELA/2 - 100, ALTURA_JANELA/2 - 60, "ESC para pausar");

    //glutSwapBuffers();
}

void drawGameOver(const Game* game) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Fundo vermelho escuro
    glClearColor(0.2f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Mensagem de game over
    glColor3f(1.0f, 0.0f, 0.0f); // Vermelho
    drawText(LARGURA_JANELA/2 - 70, ALTURA_JANELA/2 + 60, "GAME OVER");

    // Pontuação
    char scoreText[50];
    sprintf(scoreText, "Pontuacao: %d", game->score);
    glColor3f(1.0f, 1.0f, 1.0f); // Branco
    drawText(LARGURA_JANELA/2 - 50, ALTURA_JANELA/2 + 20, scoreText);

    // High score
    char highScoreText[50];
    sprintf(highScoreText, "Recorde: %d", game->highScore);
    drawText(LARGURA_JANELA/2 - 50, ALTURA_JANELA/2 - 10, highScoreText);

    // Opções
    drawText(LARGURA_JANELA/2 - 120, ALTURA_JANELA/2 - 50, "Pressione R para reiniciar");
    drawText(LARGURA_JANELA/2 - 100, ALTURA_JANELA/2 - 80, "ESC para sair");

    //glutSwapBuffers();
}

void drawHUD(const Game* game) {
    char scoreText[50];
    sprintf(scoreText, "Score: %d", game->score);

    char levelText[50];
    sprintf(levelText, "Level: %d", game->level);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawText(10, ALTURA_JANELA - 20, scoreText);
    drawText(LARGURA_JANELA - 100, ALTURA_JANELA - 20, levelText);
}