/*
Title: auxi.cpp
Description: Holds a collection of miscellaneous functions that don't fall under one group.
Author: Michael G. Oranski
ID: 2743708
Date: May 15, 2019
*/
#include "auxi.h"

/*
	Initialize the allegro library and components. Checks to make sure
	they are properly initialized. 
	Paramm:
		N/A
	Return:
		1 - problems with one of the components
		0 - all clear
*/
int initLib () {
	int check = allegro_init (); // Initialize Allegro library
	if (check != 0) {
		std::cerr << "Allegro library failed to Initialize!" << std::endl;
		return 1;
	}

	check = install_keyboard(); // Install the keyboard interrupt
	if (check != 0) {
		std::cerr << "Allegro keyboard failed to Install!" << std::endl;
		return 1;
	}

	set_color_depth(16);
	srand (time(NULL)); //Seed the random number generator

	//install a digital sound driver
    if (install_sound(DIGI_AUTODETECT, MIDI_NONE, "") != 0) 
    {
        std::cerr <<"Error initializing sound system" << std::endl;
        return 1;
    }

	return 0;
}
/*
	Choose a random sound effect and plays it.
	Param:
		street 		- A sample sound file that holds street noise.
		police1   	- A sample sound file that holds police siren noise.
		police2  	- A sample sound file that holds police siren noise.
		musicOn     - A boolean that determines whatever a music should be played
	Return:
		N/A
*/
void randSound (SAMPLE * street, SAMPLE * police1, SAMPLE * police2, bool musicOn) {
	// Sound variables 
	int volume = 50;
    int pan = 100;
    int pitch = 1000;

    int choice = rand () % 3; // Choose a random sound effect

    if (musicOn) {
    	switch (choice) {
    		case 0 	: 	//	play_sample (street, volume, pan, pitch, FALSE); // Keeps going even if music turned off
    						break;
    		case 1	:		//play_sample (police1, volume, pan, pitch, FALSE); // Keeps going even if music turned off
    						break;
    		case 2	:		play_sample (police2, volume, pan, pitch, FALSE); 
    						break;
    	}
    }
}

/*
	Releases all the SAMPLE sound resources.
*/
void freeSoundRes (SAMPLE * introEffect, SAMPLE * jump, SAMPLE * street, SAMPLE * police1, SAMPLE * police2, SAMPLE * gameOver, SAMPLE * mainMusic) {
	destroy_sample (introEffect);
	destroy_sample (jump);
	destroy_sample (street);
	destroy_sample (police1);
	destroy_sample (police2);
	destroy_sample (gameOver);
	destroy_sample (mainMusic);
}

/*
	Releases all image resources.
	Param:
		charImg 	- An array of bitmap that holds player's sprite animation
		policeImg 	- An array of bitmap that holds enemie's sprite animation
		background 	- A bitmap that holds the image of the game's background
		symbol		- A Font that represents the character's symbol
		statFont 	- A Font that represents the letters used to write info on game screen
	Return:
		N/A
*/
void freeImageRes (BITMAP * charImg [8], BITMAP * policeImg [6], BITMAP * background, FONT * symbol, FONT * statFont) {
	//Destroy player Sprites
	for (int n = 0; n < 8; n++)
		destroy_bitmap (charImg [n]);

	//Destroys enemies Sprites
	for (int n = 0; n < 6; n++)
		destroy_bitmap (policeImg [n]);

	// Destroy background
	destroy_bitmap (background);
	destroy_font (symbol);
	destroy_font (statFont);
}
