#pragma once    // однократное подключение файла
#include "SDL.h"

enum colour_t {red, green, purple};
enum direction_t {left, right, stationary};

struct score_t {

	unsigned int shots;
	unsigned int points;
	unsigned int level;
};

struct saucer_t {
	
	SDL_Rect hitbox;
	unsigned int alive;
	enum direction_t direction;
};

struct enemy_t {

	SDL_Rect hitbox;
	enum colour_t colour;
	unsigned int alive;
	unsigned int points;
};

struct invaders_t {

	struct enemy_t enemy[5][10];
	enum direction_t direction;
	unsigned int killed;
	int speed;
	int state;
	int state_speed;
	Uint32 state_time;
};

struct base_t {

	SDL_Rect hitbox;
};

struct player_t {

	SDL_Rect hitbox;
	int lives;
};

struct bullet_t {
	
	SDL_Rect hitbox;
	unsigned int alive;
};
