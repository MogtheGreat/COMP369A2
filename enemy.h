/*
Title: enemy.h
Description: Deals with enemy behavior, generation and collision.
Author: Michael G. Oranski
ID: 2743708
Date: May 15, 2019
*/
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