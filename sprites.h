/*
Title: sprites.h
Description: Defines a sprite object/class.
Author: Michael G. Oranski
ID: 2743708
Date: May 15, 2019

Note:
    Could be updated to sprite class rather than struct.
*/
#ifndef SPRITES_H
#define SPRITES_H

#define MAXSPRITES 7        // Max number of sprites in the game including player's sprite.

//define the sprite structure
typedef struct SPRITE {
	int dir, alive;
    int x,y;
    int width,height;
    int xspeed,yspeed;
    int xdelay,ydelay;
    int xcount,ycount;
    int curframe,maxframe,animdir;
    int framecount,framedelay;
    bool onScreen;
    bool placed;
}SPRITE;

#endif