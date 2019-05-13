#include <allegro.h>

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
	//FONT * title = ();
	blit (start, screen, 0,0,0,0, SCREEN_W, SCREEN_H);

	// Display start page
	// Display game page

	while (!key[KEY_ESC]) {}

	destroy_bitmap (start);
	allegro_exit ();
	return 0;
}
END_OF_MAIN()