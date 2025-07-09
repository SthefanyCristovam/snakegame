#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "game.h"  // Alterado de game" para game.h

void initGraphics();
void drawGame(const Game* game);
void drawMenu();
void drawGameOver(const Game* game);
void drawHUD(const Game* game);
void drawText(float x, float y, const char* text);  // Adicione esta declaração

#endif