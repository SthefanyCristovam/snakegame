#include <GL/freeglut.h>
#include "graphics.h"

Game game;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);  // Adicionado limpeza do buffer

    switch(game.state) {
        case GAME_MENU:
            drawMenu();
            break;

        case GAME_PLAYING:
            drawGame(&game);
            break;

        case GAME_PAUSED:
            drawGame(&game);
            // Overlay de pausa
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
            glBegin(GL_QUADS);
                glVertex2i(0, 0);
                glVertex2i(LARGURA_JANELA, 0);
                glVertex2i(LARGURA_JANELA, ALTURA_JANELA);
                glVertex2i(0, ALTURA_JANELA);
            glEnd();
            glDisable(GL_BLEND);

            glColor3f(1.0f, 1.0f, 0.0f);
            drawText(LARGURA_JANELA/2 - 40, ALTURA_JANELA/2, "PAUSADO");
            drawText(LARGURA_JANELA/2 - 100, ALTURA_JANELA/2 - 30, "Pressione ESC para continuar");
            break;

        case GAME_OVER:
            drawGameOver(&game);
            break;
    }
    glutSwapBuffers();
}

void timer(int) {
    if(game.state != GAME_PLAYING) {
        glutTimerFunc(100, timer, 0);  // Intervalo fixo para menus
        return;
    }

    updateGame(&game);
    glutPostRedisplay();
    glutTimerFunc(game.speed, timer, 0);
}

void keyboard(unsigned char key, int x, int y) {
    handleInput(&game, key, x, y);
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    handleSpecialInput(&game, key, x, y);
}

void initGL() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);  // Cor de fundo padrão
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, LARGURA_JANELA, 0, ALTURA_JANELA);
    glMatrixMode(GL_MODELVIEW);
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(LARGURA_JANELA, ALTURA_JANELA);
    glutCreateWindow("Jogo da Cobrinha - OpenGL");

    initGL();
    initGame(&game);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);  // Adicionado callback de redimensionamento
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutTimerFunc(100, timer, 0);

    // Força o primeiro redesenho
    glutPostRedisplay();

    glutMainLoop();
    return 0;
}