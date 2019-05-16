/*
Title: movement.cpp
Description: Deals with sprite's movement and player's input.
Author: Michael G. Oranski
ID: 2743708
Date: May 15, 2019
*/
#ifndef MOVEMENT_H
#define MOVEMENT_H
#include <allegro.h>
#include <iostream>
#include "sprites.h"

//Define the y position of the sprites so that they 'look' like they are on the side walk of the background. 
//48 and 50 are the sprites height while 25 is the distance to the sidewalk
#define PLAYERYPOS SCREEN_H - 48 - 25
#define ENEMYYPOS SCREEN_H - 50 - 25

void initSprites (SPRITE * people[MAXSPRITES], int charWidth, int charHeight, int enemWidth, int enemHeight);

void playerInput (SPRITE * player, SAMPLE * jump, bool & pause, bool & musicOn);

void updatePlayerSprite (SPRITE * player);

void warpsprite(SPRITE *spr);

void updateEnemySprite (SPRITE *spr);

void resetSpeed (SPRITE * player);

void freeSprite (SPRITE * people[MAXSPRITES]);

#endif