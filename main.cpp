#include <allegro.h>
#include "auxi.h"
#include "graphics.h"
#include "movement.h"
#include "enemy.h"

//timer variables
volatile int counter;
volatile int ticks;
volatile int framerate;

//calculate framerate every second
void timer1(void)
{
    counter++;
    framerate = ticks;
    ticks=0;
    rest (100);
}
END_OF_FUNCTION(timer1)

int main (void) {
	BITMAP * charImg [8];
	BITMAP * policeImg [6];
	BITMAP *buffer;
	SPRITE * people[MAXSPRITES];
	int caught = 0;
	bool pause = false;
	bool musicOn = true;

	// Sound variables 
	int volume = 200;
	int musicVolume = 255;
    int pan = 128;
    int pitch = 1000;

	if (initLib ())
		return 1;

	//install a digital sound driver
    if (install_sound(DIGI_AUTODETECT, MIDI_NONE, "") != 0) 
    {
        std::cerr <<"Error initializing sound system" << std::endl;
        return 1;
    }

	int ret = set_gfx_mode (GFX_AUTODETECT_WINDOWED, 1275, 500, 0, 0);
	if (ret != 0) {
		allegro_message ("%s\n", allegro_error);
		return 1;
	}

	SAMPLE * introEffect = load_sample("Resources/Sound/Police Siren 2.wav"); // load the sample to the program
	SAMPLE * jump = load_sample ("Resources/Sound/Jump.wav");
	SAMPLE * street = load_sample ("Resources/Sound/street.wav");
	SAMPLE * police1 = load_sample ("Resources/Sound/Police Siren 3.wav");
	SAMPLE * police2 = load_sample ("Resources/Sound/Police Chase.wav");
	SAMPLE * gameOver = load_sample ("Resources/Sound/Close Vault Or Jail Door.wav");
	SAMPLE * mainMusic = load_sample ("Resources/Music/Payday 2 Soundtrack - And Now We Run.wav");

	loadTitle(); // displays title screen for the game.
	play_sample(introEffect, volume, pan, pitch, FALSE); // Plays intro Effect
	while (!keypressed()); // Wait for player to press any key
	readkey(); // clears buffer

	//Load Resources for main gameplay
	PALETTE palette;	// Color palette for fonts.
	BITMAP * background = load_bitmap ("Resources/Background/city-sprite-background.pcx", NULL);
	FONT * symbol = load_font ("Resources/Font/Ghost Smileys (48).pcx", palette, NULL);
	FONT * statFont = load_font ("Resources/Font/Punk Army (28).pcx", palette, NULL);
	int score = 0;
	int highScore = 0;

    buffer = create_bitmap(SCREEN_W,SCREEN_H); //create double buffer
	loadSprites (charImg, policeImg); // Loads the sprites for the game.
	initSprites (people, charImg [0]->w, charImg [0]->h, policeImg[0]->w,policeImg[0]->h);
	displayBackground (screen, background, symbol, statFont, score, musicOn); // Display game page
	play_sample(mainMusic, musicVolume, pan, pitch, TRUE); // Plays intro Effect

	//lock interrupt variables
    LOCK_VARIABLE(counter);
    LOCK_VARIABLE(framerate);
    LOCK_VARIABLE(ticks);
    LOCK_FUNCTION(timer1);
    install_int(timer1, 1000);

	while ((!key[KEY_ESC])) {
		if ((caught == 0) && (pause == false)) {
			displayBackground (buffer, background, symbol, statFont, score, musicOn);
			

			if ((counter % 500 == 0) && (musicOn)) {
				randSound (street, police1, police2, musicOn);
			}
		
			playerInput (people[0], jump, pause, musicOn); // Gets the player's input
			updatePlayerSprite (people[0]); // Updates the player sprites

			if (!musicOn)
			{
				musicVolume = 0;
        		adjust_sample(mainMusic, musicVolume, pan, pitch, TRUE);
			}
			else {
				musicVolume = 255;
				adjust_sample(mainMusic, musicVolume, pan, pitch, TRUE);
			}

			genEnemy (people); //Pick some random sprites from people[], turn onScreen to true. (enemy.cpp)
			placeEnemy (people); //Place onScreen Sprite at beginning (enemy.cpp)

			for (int i = 1; i < MAXSPRITES; i++) {
				updateEnemySprite (people[i]); //Update enemy Sprites (movement.cpp)
				caughtPunk (people, i, caught); //Check for collision (enemy.cpp)
				draw_sprite (buffer, policeImg[people[i]->curframe], people[i]-> x, people[i]-> y);
			}
			checkScore (people, score); //Check for Score (enemy.cpp)

			warpsprite(people[0]); // Keep the player's sprite on screen
			draw_sprite (buffer, charImg[people[0]->curframe], people[0]-> x, people[0]-> y); // Draw player's sprite to buffer

			//update ticks
    	    ticks++;

			//update the screen
			acquire_screen ();
			blit (buffer, screen, 0,0,0,0, SCREEN_W-1, SCREEN_H-1);
			release_screen ();

			resetSpeed (people[0]); // stops the player's sprite.

			if (highScore < score)
				highScore = score;
		}
		else if (pause == true) {
			displayHelp (statFont);
			while (!keypressed()); // Wait for player to press any key
			readkey ();
			pause = false;
		}
		else {
			if (caught == 1) {
				displayGameOver (gameOver, musicOn, score, highScore);
				caught = 2;
			}

			if (key[KEY_Y]) {
				caught = 0;
				score = 0;
				initSprites (people, charImg [0]->w, charImg [0]->h, policeImg[0]->w,policeImg[0]->h);
			}
		}
	}

	freeImageRes (charImg, policeImg, background, symbol, statFont);
	freeSoundRes (introEffect, jump, street, police1, police2, gameOver, mainMusic);
	freeSprite (people);
	allegro_exit ();
	return 0;
}
END_OF_MAIN()
