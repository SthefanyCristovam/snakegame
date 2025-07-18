#include <GL/freeglut.h>
#include "graphics.h"

Game game;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    switch(game.state) {
        case GAME_MENU:
            drawMenu();
            break;

        case GAME_PLAYING:
            drawGame(&game);
            break;

        case GAME_PAUSED:
            drawGame(&game);
            drawPause(&game);
            break;

        case GAME_OVER:
            drawGameOver(&game);
            break;
    }

    glutSwapBuffers();
}

void timer(int) {
    if(game.state != GAME_PLAYING) {
        glutTimerFunc(100, timer, 0);
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
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH_SIZE, 0, WINDOW_HEIGHT_SIZE);
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
    glutInitWindowSize(WINDOW_WIDTH_SIZE, WINDOW_HEIGHT_SIZE);
    glutCreateWindow("Snake game - OpenGL");

    initGL();
    initGame(&game);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutTimerFunc(100, timer, 0);

    glutPostRedisplay();

    glutMainLoop();
    return 0;
}