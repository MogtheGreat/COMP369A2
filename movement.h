#ifndef MOVEMENT_H
#define MOVEMENT_H
#include <allegro.h>
#include <iostream>
#include "sprites.h"

#define PLAYERYPOS SCREEN_H - 48 - 25
#define ENEMYYPOS SCREEN_H - 50 - 25

void initSprites (SPRITE * people[MAXSPRITES], int charWidth, int charHeight, int enemWidth, int enemHeight);

void playerInput (SPRITE * player);

void updatePlayerSprite (SPRITE * player);

void warpsprite(SPRITE *spr);

void updateEnemySprite (SPRITE *spr);

void resetSpeed (SPRITE * player);

void freeSprite (SPRITE * people[MAXSPRITES]);

#endif