#include "movement.h"

using namespace std;

void initSprites (SPRITE * people[MAXSPRITES]) {
	for (int i = 0; i < MAXSPRITES; i++){
		people[i] = new SPRITE;

		// Player Sprite init
		if (i == 0) {

		}
		//Enemy Sprite Init
		else {

		}
	}
}

void playerInput () {

	if (key[KEY_A]) {
		cout << "Pressed A" << endl;
	}
	else if (key[KEY_D]) {
		cout << "Pressed D" << endl;
	}
	else if (key[KEY_W]) {
		cout << "Pressed W" << endl;
	}
	
	if ((key[KEY_LCONTROL] || key[KEY_RCONTROL]) && (key[KEY_M])) {
		cout << "Pressed Ctrl-M" << endl;
	}

	if ((key[KEY_LCONTROL] || key[KEY_RCONTROL]) && (key[KEY_H])) {
		cout << "Pressed Ctrl-H" << endl;
	}
}

void freeSprite (SPRITE * people[MAXSPRITES]) {
	for (int i = 0; i < MAXSPRITES; i++){
		delete people[i];
	}
}
