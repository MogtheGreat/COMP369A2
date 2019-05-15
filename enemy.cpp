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
	}
}

void placeEnemy (SPRITE * spr[MAXSPRITES]) {
	if (batchPlaced == false) {
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

