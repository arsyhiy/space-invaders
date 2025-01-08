#include "SDL.h"
#include "init.h"
static SDL_Surface *screen;
static SDL_Surface *title_screen;
void draw_string(char s[], int x, int y);
#define WIDTH 600
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

//Draw the background
void draw_background () {

	SDL_Rect src;

	src.x = 0;
	src.y = 0;
	src.w = screen->w;
	src.h = screen->h;
	
	SDL_FillRect(screen,&src,0);
}




//Draw the HUD
void draw_hud() {
	
	SDL_Rect r;
	
	r.x = WIDTH;
	r.y = 0;
	r.w = SCREEN_WIDTH - WIDTH;
	r.h = SCREEN_HEIGHT;

	SDL_FillRect(screen, &r, 41);
	
	char score_label[] = "Score";
	draw_string(score_label, WIDTH, 0);
	
	char score_num[10];
	snprintf(score_num, 10, "%d", score.points);
	draw_string(score_num, WIDTH, 20);

	char level[] = "Level";
	draw_string(level, WIDTH, 60);
	
	char level_num[2];
	snprintf(level_num, 2, "%d", score.level);
	draw_string(level_num, WIDTH, 80);
	
	char lives[] = "Lives";
	draw_string(lives, WIDTH, 120);
	
	char lives_num[2];
	snprintf(lives_num, 2, "%d", player.lives);
	draw_string(lives_num, WIDTH, 140);
	
	char author[] = "Coded by";
	draw_string(author, WIDTH, 540);
	
	char name[] = "J lambert";
	draw_string(name, WIDTH, 560);
}

//Draw the title screen
void draw_title_screen() {
	
	SDL_Rect src;
	SDL_Rect dest;

	src.x = 0;
	src.y = 0;
	src.w = title_screen->w;
	src.h = title_screen->h;

	dest.x = (SCREEN_WIDTH / 2) - (title_screen->w / 2);
	dest.y = 0;
	dest.w = title_screen->w;
	dest.h = title_screen->h;
	
	SDL_BlitSurface(title_screen, &src, screen, &dest);
}

//Draw the saucer if its alive
void draw_saucer() {

	SDL_Rect src;
	
	src.x = 0;
	src.y = 0;
	src.w = 30;
	src.h = 20;
	
	if (saucer.alive == 1) {
		
		SDL_BlitSurface(saucer_img, &src, screen, &saucer.hitbox);
	}
}

//Draw the invaders if there alive
void draw_invaders() {

	SDL_Rect src, dest;
	int i,j;
	
	src.w = E_WIDTH;
	src.h = E_HEIGHT;
	
	for (i = 0; i < 5; i++) {
		
		for (j = 0; j < 10; j++) {
			
			if (invaders.enemy[i][j].alive == 1) {
				
				//purple
				if(i == 0) {	
					
					if (invaders.state == 0) {
						
						src.x = 0;
						src.y = 0;
					
					} else {
						
						src.x = 30;
						src.y = 0;				
					}
				
				//green
				} else if (i > 0 && i < 3) {
					
					if (invaders.state == 0) {
						
						src.x = 0;
						src.y = E_HEIGHT;

					} else {
						
						src.x = 30;
						src.y = E_HEIGHT;
					}

				//red
				} else {
					
					if (invaders.state == 0) {
					
						src.x = 0;
						src.y = E_HEIGHT * 2;
					
					} else {
					
						src.x = 30;
						src.y = E_HEIGHT * 2;	
					}
				}

				dest.x = invaders.enemy[i][j].hitbox.x;
				dest.y = invaders.enemy[i][j].hitbox.y;
				dest.w = invaders.enemy[i][j].hitbox.w;
				dest.h = invaders.enemy[i][j].hitbox.h;
				
				SDL_BlitSurface(invadersmap, &src, screen, &dest);
			}
		}
	}
}

//Draw the bases
void draw_bases() {

	SDL_Rect src;

	src.x = 0;
	src.y = 0;
	src.w = BASE_WIDTH;
	src.h = BASE_HEIGHT;

	int i;

	for(i = 0; i < BASE; i++) {
		
		SDL_BlitSurface(base_img[i], &src, screen, &base[i].hitbox);
	}
}

//Draw the player
void draw_player() {

	SDL_Rect src;

	src.x = 0;
	src.y = 0;
	src.w = P_WIDTH;
	src.h = P_HEIGHT;

	SDL_BlitSurface(player_img, &src, screen, &player.hitbox);
}

//Draw both the enemy and the players bullets if there alive
void draw_bullets(struct bullet_t b[], int max) {

	//Uint8 c = SDL_MapRGB(screen->format, 255, 255, 255);
	int i;


	for (i = 0; i < max; i++) {
	
		if (b[i].alive == 1) {
		
			SDL_FillRect(screen, &b[i].hitbox, 255);
		}
	}
}

//Draw a char
int draw_char(char c, int x, int y) {

	SDL_Rect src;
	SDL_Rect dest;
	int i,j;
	char *map[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ",
			"abcdefghijklmnopqrstuvwxyz",
			"!@#$%^&*()_+{}|:\"<>?,.;'-=",
			"0123456789"};

	src.x = 0;
	src.y = 0;
	src.w = 20;
	src.h = 20;
	
	dest.x = x;
	dest.y = y;
	dest.w = 20;
	dest.h = 20;

	for (i = 0; i < 4; i++) {
	
		for(j = 0; j < strlen(map[i]); j++) {
			
			if (c == map[i][j]) {
			
				SDL_BlitSurface(cmap, &src, screen, &dest);
				return 0;
			}

			src.x += 20;
		}
	
		src.y += 20;//move down one line on the image file
		src.x = 0; //reset to start of line
	}

	return 0;
}

//Draw a string of chars
void draw_string(char s[], int x, int y) {

	int i;

	for (i = 0; i < strlen(s); i++) {
	
		draw_char(s[i],x,y);
		x += 20;
	}
}

//Draw Game Over message
void draw_game_over() {
		
	SDL_Rect src;
	SDL_Rect dest;

	src.x = 0;
	src.y = 0;
	src.w = game_over_img->w;
	src.h = game_over_img->h;

	dest.x = (WIDTH / 2) - (game_over_img->w / 2);
	dest.y = (HEIGHT / 2) - (game_over_img->h / 2);
	dest.w = game_over_img->w;
	dest.h = game_over_img->h;
	
	SDL_BlitSurface(game_over_img, &src, screen, &dest);
}



