#include <allegro.h>
#include "auxi.h"
#include "graphics.h"
#include "movement.h"

int main (void) {
	BITMAP * charImg [8];
	BITMAP * policeImg [6];
	SPRITE * people[MAXSPRITES];

	if (initLib ())
		return 1;

	int ret = set_gfx_mode (GFX_AUTODETECT_WINDOWED, 1275, 500, 0, 0);
	if (ret != 0) {
		allegro_message ("%s\n", allegro_error);
		return 1;
	}

	loadTitle(); // displays title screen for the game.
	while (!keypressed()); // Wait for player to press any key
	readkey(); // clears buffer

	//Load Resources for main gameplay
	PALETTE palette;	// Color palette for fonts.
	BITMAP * background = load_bitmap ("Resources/Background/city-sprite-background.pcx", NULL);
	FONT * symbol = load_font ("Resources/Font/Ghost Smileys (48).pcx", palette, NULL);
	FONT * statFont = load_font ("Resources/Font/Punk Army (28).pcx", palette, NULL);
	int score = 0;

	loadSprites (charImg, policeImg); // Loads the sprites for the game.
	initSprites (people);
	displayBackground (background, symbol, statFont, score); // Display game page
	draw_sprite (screen, charImg[0], 0, SCREEN_H - 48 - 25);
	draw_sprite (screen, policeImg[2], SCREEN_W - 30, SCREEN_H - 50 - 25);

	while (!key[KEY_ESC]) {
		playerInput ();
	}

	freeImageRes (charImg, policeImg, background, symbol, statFont);
	freeSprite (people);
	allegro_exit ();
	return 0;
}
END_OF_MAIN()
