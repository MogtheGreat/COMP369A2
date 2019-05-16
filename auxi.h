#ifndef AUXI_H
#define AUXI_H
#include <allegro.h>
#include <iostream>

int initLib ();

void randSound (SAMPLE * street, SAMPLE * police1, SAMPLE * police2, bool musicOn);

void freeSoundRes (SAMPLE * introEffect, SAMPLE * jump, SAMPLE * street, SAMPLE * police1, SAMPLE * police2, SAMPLE * gameOver, SAMPLE * mainMusic);

void freeImageRes (BITMAP * charImg [8], BITMAP * policeImg [6], BITMAP * background, FONT * symbol, FONT * statFont);

#endif