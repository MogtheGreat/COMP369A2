#include <allegro.h>
#define WHITE makecol (255,255,255)
#define PUNKGREEN makecol (0,255,159)
#define PUNKBLUE makecol (0,184,255)
#define PUNKDARKBLUE makecol (0,30,255)
#define PUNKPINK makecol (228, 88, 236)
#define BLACK makecol(0,0,0)

BITMAP * charImg [8];
BITMAP * policeImg [6];

BITMAP * grabframe (BITMAP * source, int width, int height, int startx, int starty, int columns, int frame) {
	BITMAP * temp = create_bitmap (width, height);

	int x = startx + (frame % columns) * width;
	int y = starty + (frame / columns) * height;

	blit (source, temp, x, y, 0, 0, width, height);

	return temp;
} 

int main (void) {
	int check = allegro_init ();
	if (check != 0)
		return 1;
	check = install_keyboard();
	if (check != 0)
		return 1;
	set_color_depth(16);

	int ret = set_gfx_mode (GFX_AUTODETECT_WINDOWED, 1275, 500, 0, 0);
	if (ret != 0) {
		allegro_message ("%s\n", allegro_error);
		return 1;
	}

	BITMAP * start = load_bitmap ("Resources/Background/StartBackground.pcx", NULL);
	PALETTE palette;	// Color palette for fonts.
	FONT * titleFont = load_font ("Resources/Font/el&font gohtic!(72).pcx", palette, NULL);
	FONT * regFont = load_font ("Resources/Font/Punkboy (28).pcx", palette, NULL);

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

	textprintf_ex (screen, hold, 0, 150, PUNKGREEN, -1, "While out at late night you were in the process of spraying");
	textprintf_ex (screen, hold, 0, 190, PUNKGREEN, -1, "graffiti when the cops spotted you down the alleyway.");
	textprintf_ex (screen, hold, 0, 230, PUNKGREEN, -1, "You decided to scram rather than stick around since getting caught");
	textprintf_ex (screen, hold, 0, 270, PUNKGREEN, -1, "means going to juvie.");
	textprintf_ex (screen, hold, 0, 310, PUNKGREEN, -1, "Avoid police by pressing W to jump over them.");
	textprintf_ex (screen, hold, 0, 350, PUNKGREEN, -1, "Move around by pressing A or D for left or right.");
	textprintf_ex (screen, hold, 300, SCREEN_H-40, WHITE, -1, "Press any key to continue.");

	while (!keypressed());
	readkey();

	//Load Resources for main gameplay
	BITMAP * background = load_bitmap ("Resources/Background/city-sprite-background.pcx", NULL);
	FONT * symbol = load_font ("Resources/Font/Ghost Smileys (48).pcx", palette, NULL);
	FONT * statFont = load_font ("Resources/Font/Punk Army (28).pcx", palette, NULL);
	int score = 0;

	//Do Sprite Stuff here
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

	// Display game page
	blit (background, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
	textprintf_ex (screen, symbol, 0,0, WHITE, -1, "Y");
	textprintf_ex (screen, statFont, 60, 0, PUNKBLUE, -1, "Score: ");
	textprintf_ex (screen, statFont, 180, 0,  PUNKBLUE, -1, "%d", score);
	draw_sprite (screen, charImg[0], 0, SCREEN_H - 48 - 25);
	draw_sprite (screen, policeImg[2], SCREEN_W - 30, SCREEN_H - 50 - 25);

	while (!key[KEY_ESC]) {}

	//Destroy Sprites
	for (int n = 0; n < 8; n++)
		destroy_bitmap (charImg [n]);

	destroy_bitmap (start);
	destroy_bitmap (background);
	destroy_font (titleFont);
	destroy_font (regFont);
	destroy_font (symbol);
	destroy_font (statFont);
	allegro_exit ();
	return 0;
}
END_OF_MAIN()