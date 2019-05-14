#ifndef SPRITES_H
#define SPRITES_H

#define MAXSPRITES 7

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
}SPRITE;

#endif