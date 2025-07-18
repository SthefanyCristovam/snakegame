#pragma once

#include "game.h"

void initGraphics();
void drawGame(const Game* game);
void drawMenu();
void drawGameOver(const Game* game);
void drawHUD(const Game* game);
void drawText(float x, float y, const char* text);
void drawTextWCentralized(const char* text, float height_offset);
void drawPause(const Game* game);
