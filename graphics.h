#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <allegro.h>
#include "sprites.h"

#define WHITE makecol (255,255,255)
#define PUNKGREEN makecol (0,255,159)
#define PUNKBLUE makecol (0,184,255)
#define PUNKDARKBLUE makecol (0,30,255)
#define BLACK makecol(0,0,0)

void loadTitle ();

BITMAP * grabframe (BITMAP * source, int width, int height, int startx, int starty, int columns, int frame);

void loadSprites (BITMAP * charImg [8], BITMAP * policeImg [6]);

void displayBackground (BITMAP * target, BITMAP * background, FONT * symbol, FONT * statFont, int score, bool musicOn);

void displayGameOver (SAMPLE * jail, bool musicOn, int score, int highScore);

void displayHelp (FONT * info);

#endif