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
	BITMAP * temp = load_bitmap ("Resources/Original/PlayerCharacterComp369(23x43).bmp", NULL);
	for (int n = 0; n < 8; n++) {
		charImg [n] = grabframe (temp, 23,43,0,0,2,n);
	}
	destroy_bitmap (temp);

	temp = load_pcx ("Resources/Enemies/Police(24x50).pcx",NULL);
	for (int n = 0; n < 6; n++) {
		policeImg [n] = grabframe (temp, 24,50,0,0,4,n);
	}
	destroy_bitmap (temp); 
}

void displayBackground (BITMAP * target, BITMAP * background, FONT * symbol, FONT * statFont, int score, bool musicOn) {
	blit (background, target, 0,0,0,0, SCREEN_W, SCREEN_H);
	textprintf_ex (target, symbol, 0,0, WHITE, -1, "Y");
	textprintf_ex (target, statFont, 60, 0, PUNKBLUE, -1, "Score: ");
	textprintf_ex (target, statFont, SCREEN_W-225, 0, PUNKBLUE, -1, "Help: Ctrl-H");
	textprintf_ex (target, statFont, 180, 0,  PUNKBLUE, -1, "%d", score);

	if (musicOn)
		textprintf_ex (target, statFont, SCREEN_W-225, 30, PUNKBLUE, -1, "Music: ON");
	else
		textprintf_ex (target, statFont, SCREEN_W-225, 30, PUNKBLUE, -1, "Music: OFF");
}

void displayGameOver (SAMPLE * jail, bool musicOn, int score, int highScore) {
	rectfill(screen,0,0,SCREEN_W, SCREEN_H, BLACK);
	PALETTE palette;

	//load resources
	FONT * gameOverFont = load_font ("Resources/Font/a dripping marker(72).pcx", palette, NULL);
	FONT * infoFont = load_font ("Resources/Font/Punkboy (28).pcx", palette, NULL);

	// Print Game over info
	textprintf_ex (screen, gameOverFont, 375, SCREEN_H/2-50, PUNKDARKBLUE, -1, "GAME OVER");
	textprintf_ex (screen, infoFont, 325, SCREEN_H - 200, PUNKDARKBLUE, -1, "You have been caught!");
	textprintf_ex (screen, infoFont, 100, SCREEN_H - 150, PUNKDARKBLUE, -1, "Score: %d", score);
	textprintf_ex (screen, infoFont, 100, SCREEN_H - 100, PUNKDARKBLUE, -1, "High Score: %d", highScore);
	textprintf_ex (screen, infoFont, 100, SCREEN_H - 50, PUNKDARKBLUE, -1, "Press Y to start over. ESC to exit.");

	if (musicOn)
		play_sample(jail, 200, 128, 1000, FALSE); // Plays intro Effect

	//Release resources
	destroy_font (gameOverFont);
	destroy_font (infoFont);
}


void displayHelp (FONT * info) {
	rectfill(screen, 0, SCREEN_H/2 -50, SCREEN_W, SCREEN_H - 150, BLACK);
	textprintf_ex (screen, info, 0, SCREEN_H/2 -50, PUNKBLUE, -1, "Press A or D to move left or right. Press W to jump.");
	textprintf_ex (screen, info, 0, SCREEN_H/2 -20, PUNKBLUE, -1, "Evade incoming police by jumping over. Score when police leaves scene.");
	textprintf_ex (screen, info, 0, SCREEN_H/2 + 10, PUNKBLUE, -1, "Turn Music on/off by press Ctrl-M. Exit game by pressing ESC.");
	textprintf_ex (screen, info, 0, SCREEN_H/2 + 40, PUNKBLUE, -1, "Press any key to resume play.");
}
