/*
Title: auxi.cpp
Description: Holds a collection of miscellaneous functions that don't fall under one group.
Author: Michael G. Oranski
ID: 2743708
Date: May 15, 2019
*/
#ifndef AUXI_H
#define AUXI_H
#include <allegro.h>
#include <iostream>

int initLib ();

void randSound (SAMPLE * street, SAMPLE * police1, SAMPLE * police2, bool musicOn);

void freeSoundRes (SAMPLE * introEffect, SAMPLE * jump, SAMPLE * street, SAMPLE * police1, SAMPLE * police2, SAMPLE * gameOver, SAMPLE * mainMusic);

void freeImageRes (BITMAP * charImg [8], BITMAP * policeImg [6], BITMAP * background, FONT * symbol, FONT * statFont);

#endif