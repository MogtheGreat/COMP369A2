#include "graphics.h"

void loadTitle() {
	// Loads resources for title
	BITMAP * start = load_bitmap ("Resources/Background/StartBackground.pcx", NULL);
	PALETTE palette;	// Color palette for fonts.
	FONT * titleFont = load_font ("Resources/Font/el&font gohtic!(72).pcx", palette, NULL);
	FONT * regFont = load_font ("Resources/Font/Punkboy (28).pcx", palette, NULL);

	// Checks for successful customer font upload. If not, use regular font.
	FONT * hold = NULL;
	if (regFont)
		hold = regFont;
	else
		hold = font;
	
	// Display start page
	blit (start, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
	if (!titleFont)
		textprintf_ex (screen, font, 200, 0, WHITE, -1, "Punk Escape!"); // Print title of the game in regular font
	else 
		textprintf_ex (screen, titleFont, 200, 0, WHITE, -1, "Punk Escape!"); // Print title of the game in custom font

	// Print out instructions
	textprintf_ex (screen, hold, 0, 150, PUNKGREEN, -1, "While out at late night you were in the process of spraying");
	textprintf_ex (screen, hold, 0, 190, PUNKGREEN, -1, "graffiti when the cops spotted you down the alleyway.");
	textprintf_ex (screen, hold, 0, 230, PUNKGREEN, -1, "You decided to scram rather than stick around since getting caught");
	textprintf_ex (screen, hold, 0, 270, PUNKGREEN, -1, "means going to juvie.");
	textprintf_ex (screen, hold, 0, 310, PUNKGREEN, -1, "Avoid police by pressing W to jump over them.");
	textprintf_ex (screen, hold, 0, 350, PUNKGREEN, -1, "Move around by pressing A or D for left or right.");
	textprintf_ex (screen, hold, 300, SCREEN_H-40, WHITE, -1, "Press any key to continue.");

	// Release resources
	destroy_bitmap (start);
	destroy_font (titleFont);
	destroy_font (regFont);
}

BITMAP * grabframe (BITMAP * source, int width, int height, int startx, int starty, int columns, int frame) {
	BITMAP * temp = create_bitmap (width, height);

	int x = startx + (frame % columns) * width;
	int y = starty + (frame / columns) * height;

	blit (source, temp, x, y, 0, 0, width, height);

	return temp;
}

void loadSprites (BITMAP * charImg [8], BITMAP * policeImg [6]) {
	BITMAP * temp = load_pcx ("Resources/Original/PlayerCharacterComp369(48x48).pcx", NULL);
	for (int n = 0; n < 8; n++) {
		charImg [n] = grabframe (temp, 48,48,0,0,2,n);
	}
	destroy_bitmap (temp);

	temp = load_pcx ("Resources/Enemies/Police(24x50).pcx",NULL);
	for (int n = 0; n < 6; n++) {
		policeImg [n] = grabframe (temp, 24,50,0,0,4,n);
	}
	destroy_bitmap (temp); 
}

void displayBackground (BITMAP * target, BITMAP * background, FONT * symbol, FONT * statFont, int score) {
	blit (background, target, 0,0,0,0, SCREEN_W, SCREEN_H);
	textprintf_ex (target, symbol, 0,0, WHITE, -1, "Y");
	textprintf_ex (target, statFont, 60, 0, PUNKBLUE, -1, "Score: ");
	textprintf_ex (target, statFont, 180, 0,  PUNKBLUE, -1, "%d", score);
}
