/*
Title: movement.cpp
Description: Deals with sprite's movement and player's input.
Author: Michael G. Oranski
ID: 2743708
Date: May 15, 2019
*/
#include "movement.h"

using namespace std;

bool jumped = false; //Player in the air or not. If in the air, can't jump again

/*
    Initializes the SPRITE array to allow for sprite movement.
    Param:
        people         - A SPRITE that holds the information about all the moveable sprites in the game.
        MAXSPRITES  - An integer that determines the max number of sprites in the game.
        charWidth   - the width of the player's character
        charHeight  - the height of the player's character
        enemWidth   - the width of the enemies character
        enemHeight  - the height of the enemies character
    Return:
        N/A
    Note:
        charWidth or charHeight are different from enemWidth or enemHeight. 
*/
void initSprites (SPRITE * people[MAXSPRITES], int charWidth, int charHeight, int enemWidth, int enemHeight) {
	for (int i = 0; i < MAXSPRITES; i++){
		people[i] = new SPRITE;

		// Player Sprite init
		if (i == 0) {
			people[i]-> x = SCREEN_W/2;
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
			people[i]->xdelay = 3;		// Affect time
			people[i]->ydelay = 0;
			people[i]->xcount = 1;
			people[i]->ycount = 0;
			people[i]->xspeed = 5;		// Allows movement right(positive)/left(negative) screen
			people[i]->yspeed = 0;		// Allows movement up(negative)/down(positive) screeen
			people[i]->curframe = 0;
			people[i]->maxframe = 5;
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
			people[i]->xdelay = 4;		// Affect time
			people[i]->ydelay = 0;
			people[i]->xcount = 1;
			people[i]->ycount = 0;
			people[i]->xspeed = -5;		// Allows movement right(positive)/left(negative) screen
			people[i]->yspeed = 0;		// Allows movement up(negative)/down(positive) screeen
			people[i]->curframe = 0;
			people[i]->maxframe = 5;
			people[i]->framecount = 0;
			people[i]->framedelay = 1;
			people[i]->animdir = 1;
			people[i]-> onScreen = false;
            people[i]-> placed = false;
		}
	}
}

/*
    Collects player's input and either modifies the player's sprite, call help module or
    turn music on/off based on input.
    Param:
        player  - A SPRITE that represents the player's sprite
        jump    - A SAMPLE that represents a cartoonist jumping sound effect
        pause   - A reference to a boolean variable that represents the game being paused or not
        musicOn - A reference to a boolean variable that represents the game music being on or off
    Return:
        N/A
*/
void playerInput (SPRITE * player, SAMPLE * jump, bool & pause, bool & musicOn) {
int count = 0;
    //Player moves to the left
	if (key[KEY_A]) {
		player -> xspeed = -2;
	}
    //Player moves to the rights
	else if (key[KEY_D]) {
		player -> xspeed = 2;
	}
    //If player has not jump, jumps
	if ((key[KEY_W]) && jumped == false) {

		player -> yspeed = -12;
		jumped = true; // Used to disallow multi jumping

        // Plays jump sound if music is on
        if ((musicOn) && (count == 0)) {
            play_sample(jump, 200, 128, 1000, FALSE); // Plays jump Effect
            count = 1; //Used to prevent multiple calls. May not be needed
        }
	}
	
    // if Player press ctrl-m, turn music on/off
	if ((key[KEY_LCONTROL] || key[KEY_RCONTROL]) && (key[KEY_M])) {
        if (musicOn)
    		musicOn = false;
        else
            musicOn = true;
	}

    //If player press crtrl-h, pause game
	if ((key[KEY_LCONTROL] || key[KEY_RCONTROL]) && (key[KEY_H])) {
        if (pause)
            pause = false;
        else
            pause = true;
        readkey (); //Clears input buffer
	}
}

/*
    Updates the player's sprite position based on
    sprite xspeed/yspeed. Changes the animation frame.
    Param:
        player  - A SPRITE that represents the player's sprite
    Return:
        N/A
*/
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

    	// Player moving towards the right, plays right moving animation
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

    	//Player moving towars the left, plays left moving animation
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

/*
    If the sprite goes off screen, warps the sprite to the other end.

    Param:
        spr        - A SPRITE that represents any sprite
    Return:
        N/A
    Note: Function taken from main.c of the interruptTest program
    Program from Game Programming All In One, Third Edition
*/
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

/*
     Updates the enemies's sprite position based on
    sprite xspeed/yspeed. Changes the animation frame.
    Param:
        spr        - A SPRITE that represents any sprite
    Return:
        N/A
*/
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

    	   //Moving to the right, change to right animation
    	   if (spr-> xspeed < 0) {
    		  if (spr->animdir == -1)
        	   {
            	   if (--spr->curframe < 0)
                	   spr->curframe = 2;
        	   }
       		   else if (spr->animdir == 1)
        	   {
            	   if (++spr->curframe > 2)
            		  spr->curframe = 0;
        	   }
    	    }

    	   //Moving to the left, change to left animatino
    	   else if (spr -> xspeed > 0){
    		  if (spr->animdir == -1)
        	   {
            	   if (--spr->curframe < 3)
                	   spr->curframe = 5;
        	   }
       		   else if (spr->animdir == 1)
        	   {
            	   if (++spr->curframe > 5)
            		  spr->curframe = 3;
        	   }
    	   }
        }
    }
}

/*
    Resets the player's sprite xspeed to zero. Modifies
    the yspeed based on position in air, if jumping.
    Param:
        player  - A SPRITE that represents the player's sprite
    Return:
        N/A
*/
void resetSpeed (SPRITE * player) {
	player->xspeed = 0;

	//Player on the ground
	if ((jumped == true) && (player-> y == PLAYERYPOS)){
		player -> yspeed = 0;
		jumped = false;
	}

	// Begin player's descent after peak
	if ((jumped == true) && (player -> yspeed == 0) && (player-> y != PLAYERYPOS))
		player -> yspeed = 2;
}

/*
    Frees all SPRITE info.
    Param:
        people         - A SPRITE that holds the information about all the moveable sprites in the game.
        MAXSPRITES  - An integer that determines the max number of sprites in the game.
    Return:
        N/A
    Note:
        Could be move into auxi.cpp or into a sprite.cpp since does not have anything
        to do with movement.
*/
void freeSprite (SPRITE * people[MAXSPRITES]) {
	for (int i = 0; i < MAXSPRITES; i++){
		delete people[i];
	}
}
