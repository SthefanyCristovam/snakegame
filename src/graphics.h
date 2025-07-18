#pragma once

#include "game.h"

void initGraphics();
void drawGame(const Game* game);
void drawMenu();
void drawGameOver(const Game* game);
void drawHUD(const Game* game);
void drawTextCustomAxis(float x, float y, const char* text);
