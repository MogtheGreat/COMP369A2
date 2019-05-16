#include "enemy.h"

bool batchPlaced = false;

void genEnemy (SPRITE * spr[MAXSPRITES]) {
	if (batchPlaced == false) {
		int randNum = rand () % 5 + 1;
		int randChoice = -1;

		for (int i = 0; i < randNum; i++) {
			randChoice = (rand () % (MAXSPRITES-1)) + 1; //Minus one due to not counting player sprite. Plus one to avoid 0 and
			SPRITE * hold = spr [randChoice];

			if (hold-> onScreen == false) {
				hold-> onScreen = true;
			}
		}
		batchPlaced = true;
	}
}

void placeEnemy (SPRITE * spr[MAXSPRITES]) {
	if (batchPlaced == true) {
		for (int i = 1; i < MAXSPRITES; i++) {
			if ((spr [i]-> onScreen == true) && (spr[i]-> placed == false)) {
				spr[i]-> placed = true;

				if (spr[i]-> xspeed > 0)
					spr[i]-> x = 0;
				else 
					spr[i]-> x = SCREEN_W;
			}
		}
	}
}

void checkScore (SPRITE * spr[MAXSPRITES], int & score) {
	if (batchPlaced == true) {
		for (int i = 1; i < MAXSPRITES; i++) {
			if ((spr [i]-> onScreen == true) && (spr[i]-> placed == true)) {
				if ((spr[i]-> xspeed > 0) && (spr[i]-> x >= SCREEN_W)) {
					spr[i] ->onScreen = false;
					spr[i]-> placed = false;
					score += 100;
				}
				else if ((spr[i]-> xspeed < 0) && (spr[i]-> x <= 0)) {
					spr[i] ->onScreen = false;
					spr[i]-> placed = false;
					score += 100;
				}
			}
		}
		batchPlaced = false;
	}
}

/*
	Note: Function taken from main.c of the collisionTest program
	Program from Game Programming All In One, Third Edition
*/
int inside(int x,int y,int left,int top,int right,int bottom)
{
    if ((x > left && x < right) && (y <= bottom))
        return 1;
    else
        return 0;
}

/*
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

void caughtPunk (SPRITE * spr[MAXSPRITES], int current, int & caught) {
	if (collided(spr[current], spr[0], 0)) {
		if (caught == 0) {
			caught = 1;
		}
	}
}
