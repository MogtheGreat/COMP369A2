/*
Title: enemy.cpp
Description: Deals with enemy behavior, generation and collision.
Author: Michael G. Oranski
ID: 2743708
Date: May 15, 2019
*/
#include "enemy.h"

bool batchPlaced = false; //Prevents a stream of enemies from occuring. 

/*
	Generate a batch of enemies. Number of enemies varies each time.

	Param:
		spr 		- A SPRITE that holds the information about all the moveable sprites in the game.
		MAXSPRITES 	- An integer that determines the max number of sprites in the game.
	Return:
		N/A
*/
void genEnemy (SPRITE * spr[MAXSPRITES]) {
	if (batchPlaced == false) { // No batch placed
		int randNum = rand () % 5 + 1; 	// choose random number to be placed
		int randChoice = -1;

		for (int i = 0; i < randNum; i++) {
			randChoice = (rand () % (MAXSPRITES-1)) + 1; //Minus one due to not counting player sprite. Plus one to avoid 0 and
			SPRITE * hold = spr [randChoice]; // choose a random sprite

			if (hold-> onScreen == false) { // Mark the sprite to be placed on screen
				hold-> onScreen = true;
			}
		}
		batchPlaced = true;
	}
}

/*
	Place the enemies on the screen. Assign each enemy a random speed.
	Param:
		spr 		- A SPRITE that holds the information about all the moveable sprites in the game.
		MAXSPRITES 	- An integer that determines the max number of sprites in the game.
	Return:
		N/A
*/
void placeEnemy (SPRITE * spr[MAXSPRITES]) {
	if (batchPlaced == true) { // if batch has been generated
		for (int i = 1; i < MAXSPRITES; i++) {
			if ((spr [i]-> onScreen == true) && (spr[i]-> placed == false)) { // Sprite generated but not placed
				spr[i]-> placed = true;

				// If xspeed is positive, placed to the left and randomize the speed
				if (spr[i]-> xspeed > 0) {
					spr[i]-> x = 0;
					spr[i]-> xspeed = rand() % 5 + 1;
				}
				//Xspeed is negatie, placed to the right and randomize a negative speed.
				else{
					spr[i]-> x = SCREEN_W;
					spr[i]-> xspeed = (-1)*(rand()%5) -1;
				} 
			}
		}
	}
}

/*
	Checks to see if sprite has made it to the other side. If so
	increase player's score by 100 for successful evasion.
*/
void checkScore (SPRITE * spr[MAXSPRITES], int & score) {
	if (batchPlaced == true) {
		for (int i = 1; i < MAXSPRITES; i++) {
			if ((spr [i]-> onScreen == true) && (spr[i]-> placed == true)) { // If both generated and placed on screen
				if ((spr[i]-> xspeed > 0) && (spr[i]-> x >= SCREEN_W)) { // If positive speed and reached the right side
					spr[i] ->onScreen = false; // reset sprite
					spr[i]-> placed = false;
					score += 100; // Add points
				}
				else if ((spr[i]-> xspeed < 0) && (spr[i]-> x <= 0)) { // If negative speed and reached the left side
					spr[i] ->onScreen = false; // reset sprite
					spr[i]-> placed = false;
					score += 100; // Add points
				}
			}
		}
		batchPlaced = false; // Allow for new batch to be generated
	}
}

/*
	Check to see if sprite's are inside each other boundaries.

	Note: Function taken from main.c of the collisionTest program
	Program from Game Programming All In One, Third Edition

	Return:
	 	1 = inside the boundary, collision
	 	0 = outside the boundary, no collosion
*/
int inside(int x,int y,int left,int top,int right,int bottom)
{
    if ((x > left && x < right) && (y <= bottom))
        return 1;
    else
        return 0;
}

/*
	Compares two sprites to see if one has collided with the other
	Param:
		first 	- A SPRITE to be compared
		second 	- A SPRITE to be compared
		border 	- An int that affects the sensitivity of the collision.
	Return:
		1 	- Sprites have collided
		0 	- No collision
	Note: Function taken from main.c of the collisionTest program
	Program from Game Programming All In One, Third Edition
*/
int collided(SPRITE *first, SPRITE *second, int border)
{
  //get width/height of both sprites
  int width1 = first->x + first->width;
  int height1 = first->y + first->height;
  int width2 = second->x + second->width;
  int height2 = second->y + second->height;

  //see if corners of first are inside second boundary
  if (inside(first->x, first->y, second->x + border, 
        second->y + border, width2 - border, height2 - border))
      return 1;
  if (inside(first->x, height1, second->x + border, 
        second->y + border, width2 - border, height2 - border))
      return 1;
  if (inside(width1, first->y, second->x + border, 
        second->y + border, width2 - border, height2 - border))
      return 1;
  if (inside(width1, height1, second->x + border, 
        second->y + border, width2 - border, height2 - border))
      return 1;

  //no collisions?
  return 0;
}

/*
	Checks for Collision with player's sprite. If collision then player
	is caught.
	Param:
		spr 		- A SPRITE that holds the information about all the moveable sprites in the game.
		MAXSPRITES 	- An integer that determines the max number of sprites in the game.
		current 	- Determines which enemy sprite to check
		Caught 		- A reference to an integer. 0 means not caught. Positive means caught.
	Return:
		N/A
*/
void caughtPunk (SPRITE * spr[MAXSPRITES], int current, int & caught) {
	if (collided(spr[current], spr[0], 0)) {
		if (caught == 0) {
			caught = 1;
		}
	}
}
