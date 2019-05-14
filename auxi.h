#ifndef AUXI_H
#define AUXI_H
#include <allegro.h>
#include <iostream>

int initLib ();

void freeImageRes (BITMAP * charImg [8], BITMAP * policeImg [6], BITMAP * background, FONT * symbol, FONT * statFont);

#endif