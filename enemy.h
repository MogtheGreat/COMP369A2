#ifndef ENEMY_H
#define ENEMY_H
#include <allegro.h>
#include <iostream>
#include "sprites.h"

void genEnemy (SPRITE * spr[MAXSPRITES]);

void placeEnemy (SPRITE * spr[MAXSPRITES]);

void checkScore (SPRITE * spr[MAXSPRITES], int & score);

int collided(SPRITE *first, SPRITE *second, int border);

void caughtPunk (SPRITE * spr[MAXSPRITES],int current, int & caught);

#endif