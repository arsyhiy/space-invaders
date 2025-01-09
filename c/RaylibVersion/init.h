#pragma once    // однократное подключение файла
                
#include "SDL.h"

#define BASE 4
#define BASE_WIDTH 60
#define BASE_HEIGHT 40
#define P_BULLETS 1
#define E_BULLETS 3

#include "load_image.h"



#include "structure.h"

extern struct invaders_t invaders;
extern struct score_t score;
extern struct player_t player;
extern struct saucer_t saucer;
extern struct base_t base[BASE];



//global variables, for convenience.
static SDL_Surface *cmap;
static SDL_Surface *invadersmap;
static SDL_Surface *player_img;
static SDL_Surface *saucer_img;
static SDL_Surface *base_img[4];
static SDL_Surface *damage_img;
static SDL_Surface *damage_top_img;
static SDL_Surface *game_over_img;

#define SCREEN_WIDTH 800 
#define SCREEN_HEIGHT 600
#define E_WIDTH 30
#define WIDTH 600 
#define HEIGHT 600
#define E_WIDTH 30
#define E_HEIGHT 30
#define P_WIDTH 30
#define P_HEIGHT 10
#define B_WIDTH 5
#define B_HEIGHT 15






//Initialize the score structure and game state
void init_score() {

	score.shots = 0;
	score.points = 0;
	score.level = 1;
}

//Initialize the enemies starting positions, direction, speed and colour
void init_invaders() {
	
	invaders.direction = right;
	invaders.speed = 1;
	invaders.state = 0;
	invaders.killed = 0;
	invaders.state_speed = 1000;
	invaders.state_time = SDL_GetTicks();

	int i,j;
	int x = 0;
	int y = 30;
	
	for (i = 0; i < 5; i++) {
	
		for (j = 0; j < 10; j++) {
		
			invaders.enemy[i][j].alive = 1;
			invaders.enemy[i][j].hitbox.x = x;
			invaders.enemy[i][j].hitbox.y = y;
			invaders.enemy[i][j].hitbox.w = E_WIDTH;
			invaders.enemy[i][j].hitbox.h = E_HEIGHT;
			
			x += E_WIDTH + 15; // gap size
			
			if (i == 0) {
				
				invaders.enemy[i][j].colour = purple;
				invaders.enemy[i][j].points = 30;
	
			} else if (i >= 1 && i < 3) {
			
				invaders.enemy[i][j].colour = green;
				invaders.enemy[i][j].points = 20;
		
			} else {
		
				invaders.enemy[i][j].colour = red;
				invaders.enemy[i][j].points = 10;
			}
		}
		
		x = 0; //reset line
		y += E_HEIGHT + 15;
	}
}

//Initialize the player starting position and dimensions
void init_player() {

	player.hitbox.x = (WIDTH / 2) - (P_WIDTH / 2);
	player.hitbox.y = HEIGHT - (P_HEIGHT + 10);
	player.hitbox.w = P_WIDTH;
	player.hitbox.h = P_HEIGHT;
	player.lives = 3;
}

//Initialize the bases starting position and dimensions
void init_bases() {

	int i;
	int base_total = BASE_WIDTH * 4;
	int space_left = WIDTH - base_total;
	int even_space = space_left / 5; // 5 gaps
	int x = even_space;
	int y = 500;

	for (i = 0; i < BASE; i++) {
		
		base[i].hitbox.x = x;
		base[i].hitbox.y = y;
		base[i].hitbox.w = BASE_WIDTH;
		base[i].hitbox.h = BASE_HEIGHT;
		
		x += BASE_WIDTH + even_space; //distance apart
	}

    load_image("base.bmp", &base_img[0], magenta);
	load_image("base.bmp", &base_img[1], magenta);
	load_image("base.bmp", &base_img[2], magenta);
    load_image("base.bmp", &base_img[3], magenta);
}

//Initialize the player bullets dimensions
void init_bullets(struct bullet_t b[], int max) {

	int i;

	for (i = 0; i < max; i++) {
	
		b[i].alive = 0;
		b[i].hitbox.x = 0;
		b[i].hitbox.y = 0;
		b[i].hitbox.w = B_WIDTH;
		b[i].hitbox.h = B_HEIGHT;
	}
}

//Initialize the saucer position and dimensions
void init_saucer() {

	saucer.hitbox.x = 0;	
	saucer.hitbox.y	= 0;
	saucer.hitbox.w	= 30;
	saucer.hitbox.h = 20;
	saucer.alive = 0;
	saucer.direction = right;
}




