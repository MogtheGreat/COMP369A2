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