#ifndef MOVEMENT_H
#define MOVEMENT_H
#include <allegro.h>
#include <iostream>
#include "sprites.h"

void initSprites (SPRITE * people[MAXSPRITES]);

void playerInput ();

void freeSprite (SPRITE * people[MAXSPRITES]);

#endif