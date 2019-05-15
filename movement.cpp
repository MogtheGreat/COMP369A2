#include "movement.h"

using namespace std;

bool jumped = false; //Player in the air or not. If in the air, can't jump again

void initSprites (SPRITE * people[MAXSPRITES], int charWidth, int charHeight, int enemWidth, int enemHeight) {
	for (int i = 0; i < MAXSPRITES; i++){
		people[i] = new SPRITE;

		// Player Sprite init
		if (i == 0) {
			people[i]-> x = 0;
			people[i]-> y = PLAYERYPOS;
			people[i]->width = charWidth;
			people[i]->height = charHeight;
			people[i]->xdelay = 0;		// Affect time
			people[i]->ydelay = 0;
			people[i]->xcount = 1;
			people[i]->ycount = 0;
			people[i]->xspeed = 0;		// Allows movement right(positive)/left(negative) screen
			people[i]->yspeed = 0;		// Allows movement up(negative)/down(positive) screeen
			people[i]->curframe = 0;
			people[i]->maxframe = 8;
			people[i]->framecount = 0;
			people[i]->framedelay = 1;
			people[i]->animdir = 1;
		}
		//Enemy Sprite Init Right face
		else if ((i %2 ) == 0){
			people[i]-> x = 0;
			people[i]-> y = ENEMYYPOS;
			people[i]->width = enemWidth;
			people[i]->height = enemHeight;
			people[i]->xdelay = 1;		// Affect time
			people[i]->ydelay = 0;
			people[i]->xcount = 1;
			people[i]->ycount = 0;
			people[i]->xspeed = 5;		// Allows movement right(positive)/left(negative) screen
			people[i]->yspeed = 0;		// Allows movement up(negative)/down(positive) screeen
			people[i]->curframe = 0;
			people[i]->maxframe = 6;
			people[i]->framecount = 0;
			people[i]->framedelay = 1;
			people[i]->animdir = 1;
			people[i]-> onScreen = false;
            people[i]-> placed = false;
		}
		//Enemy Sprite Init Left face
		else {
			people[i]-> x = SCREEN_W;
			people[i]-> y = ENEMYYPOS;
			people[i]->width = enemWidth;
			people[i]->height = enemHeight;
			people[i]->xdelay = 1;		// Affect time
			people[i]->ydelay = 0;
			people[i]->xcount = 1;
			people[i]->ycount = 0;
			people[i]->xspeed = -5;		// Allows movement right(positive)/left(negative) screen
			people[i]->yspeed = 0;		// Allows movement up(negative)/down(positive) screeen
			people[i]->curframe = 0;
			people[i]->maxframe = 6;
			people[i]->framecount = 0;
			people[i]->framedelay = 1;
			people[i]->animdir = 1;
			people[i]-> onScreen = false;
            people[i]-> placed = false;
		}
	}
}

void playerInput (SPRITE * player) {

	if (key[KEY_A]) {
		player -> xspeed = -2;
	}
	else if (key[KEY_D]) {
		player -> xspeed = 2;
	}
	if ((key[KEY_W]) && jumped == false) {
		player -> yspeed = -12;
		jumped = true;
	}
	
	if ((key[KEY_LCONTROL] || key[KEY_RCONTROL]) && (key[KEY_M])) {
		cout << "Pressed Ctrl-M" << endl;
	}

	if ((key[KEY_LCONTROL] || key[KEY_RCONTROL]) && (key[KEY_H])) {
		cout << "Pressed Ctrl-H" << endl;
	}
}

void updatePlayerSprite (SPRITE * player) {
	//update x position
	if (++player->xcount > player->xdelay)
    {
        player->xcount = 0;
        player->x += player->xspeed;
    }

    //update y position
    if (++player->ycount > player->ydelay)
    {
        player->ycount = 0;
        player->y += player->yspeed;
    }

    //update frame based on animdir
    if (++player->framecount > player->framedelay) {
    	player-> framecount = 0; // resets framecount
    	
    	// Player character is jumping to the right
    	if ((player-> yspeed < 0)) {
    		player-> curframe = 3;
  			player-> yspeed += 1;
    	}
    	//Player is jumping to the lefts
    	else if ((player-> yspeed < 0) && (player-> xspeed > 0)) {
    		player-> curframe = 7;
    		player-> yspeed += 1;
    	}

    	// Player moving towards the right
    	else if (player-> xspeed > 0) {
    		if (player-> animdir == -1) {
    			if (--player->curframe < 0)
    				player-> curframe = 2;
    		}
    		else if (player-> animdir == 1) {
    			if (++player-> curframe > 2)
    				player-> curframe = 0;
    		}
    	}

    	//Player moving towars the left
    	else if (player-> xspeed < 0) {
    		if (player-> animdir == -1) {
    			if (--player->curframe < 0)
    				player-> curframe = 6;
    		}
    		else if (player-> animdir == 1) {
    			if (++player-> curframe > 2)
    				player-> curframe = 4;
    		}
    	}

    	//Player standing still
    	else if (player-> xspeed == 0) {
    		player-> curframe = 0;
    	}
    }
}

void warpsprite(SPRITE *spr) {
    //simple screen warping behavior
    //Allegro takes care of clipping
    if (spr->x < 0 - spr->width)
    {
        spr->x = SCREEN_W;
    }

    else if (spr->x > SCREEN_W)
    {
        spr->x = 0 - spr->width;
    }

    if (spr->y < 0)
    {
        spr->y = SCREEN_H - spr->height-1;
    }

    else if (spr->y > SCREEN_H - spr->height)
    {
        spr->y = 0;
    }
}

void updateEnemySprite (SPRITE *spr) {
	//update x position
    if (spr -> onScreen == true) {
        if (++spr->xcount > spr->xdelay)
        {
            spr->xcount = 0;
            spr->x += spr->xspeed;
        }

        //update y position
        if (++spr->ycount > spr->ydelay)
        {   
            spr->ycount = 0;
            spr->y += spr->yspeed;
        }

        //update frame based on animdir
        if (++spr->framecount > spr->framedelay) {
    	   spr->framecount = 0;

    	   //Moving to the right
    	   if (spr-> xspeed > 0) {
    		  if (spr->animdir == -1)
        	   {
            	   if (--spr->curframe < 0)
                	   spr->curframe = 2;
        	   }
       		   else if (spr->animdir == 1)
        	   {
            	   if (++spr->curframe > spr->maxframe)
            		  spr->curframe = 0;
        	   }
    	    }

    	   //Moving to the left
    	   else if (spr -> yspeed < 0){
    		  if (spr->animdir == -1)
        	   {
            	   if (--spr->curframe < 0)
                	   spr->curframe = 5;
        	   }
       		   else if (spr->animdir == 1)
        	   {
            	   if (++spr->curframe > spr->maxframe)
            		  spr->curframe = 3;
        	   }
    	   }
        }
    }
}

void resetSpeed (SPRITE * player) {
	player->xspeed = 0;

	//Player on the ground
	if ((jumped == true) && (player-> y == PLAYERYPOS)){
		player -> yspeed = 0;
		jumped = false;
	}

	// Begin descent
	if ((jumped == true) && (player -> yspeed == 0) && (player-> y != PLAYERYPOS))
		player -> yspeed = 2;
}

void freeSprite (SPRITE * people[MAXSPRITES]) {
	for (int i = 0; i < MAXSPRITES; i++){
		delete people[i];
	}
}
