#include "auxi.h"

int initLib () {
	int check = allegro_init ();
	if (check != 0) {
		std::cerr << "Allegro library failed to Initialize!" << std::endl;
		return 1;
	}

	check = install_keyboard();
	if (check != 0) {
		std::cerr << "Allegro keyboard failed to Install!" << std::endl;
		return 1;
	}

	set_color_depth(16);
	srand (time(NULL));

	return 0;
}

void randSound (SAMPLE * street, SAMPLE * police1, SAMPLE * police2, bool musicOn) {
	// Sound variables 
	int volume = 50;
    int pan = 100;
    int pitch = 1000;

    int choice = rand () % 4;

    if (musicOn) {
    	switch (choice) {
    		case 1 	: 	//	play_sample (street, volume, pan, pitch, FALSE); // Keeps going even if music turned off
    						break;
    		case 2	:		//play_sample (police1, volume, pan, pitch, FALSE); // Keeps going even if music turned off
    						break;
    		case 3	:		play_sample (police2, volume, pan, pitch, FALSE); 
    						break;
    	}
    }
}

void freeSoundRes (SAMPLE * introEffect, SAMPLE * jump, SAMPLE * street, SAMPLE * police1, SAMPLE * police2, SAMPLE * gameOver, SAMPLE * mainMusic) {
	destroy_sample (introEffect);
	destroy_sample (jump);
	destroy_sample (street);
	destroy_sample (police1);
	destroy_sample (police2);
	destroy_sample (gameOver);
	destroy_sample (mainMusic);
}

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