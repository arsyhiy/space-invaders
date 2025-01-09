#pragma once    // однократное подключение файла
#include "SDL.h"



unsigned int pause_len;
Uint32 pause_time;
Uint32 title_time;

extern enum state_t state;

//Determin when to pause game and how long for
void pause_game() {

	if (SDL_GetTicks() > pause_time + pause_len) {
	
		state = game;
	}
}

//Set amount of time to pause game for
void pause_for(unsigned int len) {

	state = pause;
	pause_time = SDL_GetTicks();
	pause_len = len;
}
