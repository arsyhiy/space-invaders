//known bugs
//some times the bullet wont go past through a base if it hits on the far left edge. cause unknowen
//its the same bug that i found in my invaders drawing code. using the objects own hitbox as the SDL_Rect
//as the destination rectangle to blit to. using a seperate local rect in the drawing code solves it.

#include <stdlib.h>
#include <stdio.h>
#include "SDL/SDL.h"

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

#include "load_image.h"
#include "init.h"
//#include "structure.h" // игнорируй сообщение
#include "move.h"
#include "damage.h"
#include "collision.h"
#include "time.h"
#include "ai.h"
#include "calc.h"
#include "player.h"
#include "draw.h"


enum state_t {menu, options, game, game_over, pause};
extern enum state_t state;
extern Uint32 title_time; 

// Main programm
int main() {

    /* Initialize SDL's video system and check for errors */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {

        printf("Unable to Initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    /* Make sure SDL_Quit gets called when the prorgamm exits! */
    atexit(SDL_Quit);

    /*set window title*/
    SDL_WM_SetCaption("Space invaders", "P");

    /* Attempt to set a 800x600 8 bit colur video mode */
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 8, SDL_DOUBLEBUF);

    if (screen == NULL) {

        printf("Unable to set video mode: %s\n", SDL_GetError());
        return 1; 
    }

    //load images
	load_image("titlescreen.bmp", &title_screen, magenta);
	load_image("cmap.bmp", &cmap, magenta);
	load_image("invaders.bmp", &invadersmap, magenta);
	load_image("player.bmp", &player_img, magenta);
	load_image("saucer.bmp", &saucer_img, magenta);
	load_image("gameover.bmp", &game_over_img, magenta);
	load_image("damage.bmp", &damage_img, lime);
	load_image("damagetop.bmp", &damage_top_img, lime);

	Uint32 next_game_tick = SDL_GetTicks();
	int sleep = 0;
	Uint8 *keystate = 0;
	int quit = 0;
	SDL_Event event;

	init_score();
	init_invaders();
	init_bases();
	init_player();
	init_saucer();
	init_bullets(bullets, P_BULLETS);
	init_bullets(e_bullets, E_BULLETS);
	state = menu;
	title_time = SDL_GetTicks();

    /* Animate */
	while (quit == 0) {
		
		/* Grab a snapshot of the keyboard. */
		keystate = SDL_GetKeyState(NULL);
		
		while (SDL_PollEvent(&event)) {

			switch(event.type) {
				
				case SDL_KEYDOWN:
					
					switch( event.key.keysym.sym ) {
					
						//exit out of game loop if escape is pressed
						case SDLK_ESCAPE:
							
							quit = 1;
						break;
						
						case SDLK_SPACE:	
						
							if (state == menu) {

								state = game;

							} else if (state == game){
								
								player_shoot();
								saucer_ai();
							
							} else if (state == game_over) {
							
								init_invaders();
								init_bases();
								init_score();
								init_player();
								state = game;
							}
						break;
						
						default:
						break;
					}
				break;
			}
		}
	
		draw_background();

		if (state == menu) {
			
			char s[] = "Press SPACEBAR to start";
			SDL_Rect src[60];
			
			int i;

			if (title_time + 2000 < SDL_GetTicks())  {
			
				src[0].x = 180;
				src[0].y = 40;
				src[0].w = 440;
				src[0].h = 230;
			
				SDL_FillRect(screen, &src[0], 248);
			
			} else {
			
				int y = 0;

				for (i = 0; i < 60; i++) {
				
					src[i].x = 0;
					src[i].y = y;
					src[i].w = SCREEN_WIDTH;
					src[i].h = 10;

					SDL_FillRect(screen, &src[i], 227);
				
					y += 10;							
				}
			
				for (i = 0; i < 60; i++) {

					SDL_FillRect(screen, &src[i], rand() % 255);

				}
			}
			
			draw_title_screen();	
			draw_string(s, (SCREEN_WIDTH / 2) - (strlen(s) * 10), 500);

		} else if (state == game) {

			//move player
			if (keystate[SDLK_LEFT]) {
				
				move_player(left);
			}

			if (keystate[SDLK_RIGHT]) {
				
				move_player(right);
			}

			draw_hud();
			draw_player();
			draw_bases();
			draw_invaders();
			draw_saucer();
			draw_bullets(bullets, P_BULLETS);
			draw_bullets(e_bullets, E_BULLETS);
			enemy_hit_collision();
			player_hit_collision();
			enemy_base_collision();
			saucer_hit_collision();
			bullet_base_collision(e_bullets, E_BULLETS, 1);
			bullet_base_collision(bullets, P_BULLETS, 0);
			enemy_player_collision();
			move_invaders(invaders.speed);
			move_saucer();
			move_bullets(bullets, P_BULLETS, -30);
			move_bullets(e_bullets, E_BULLETS, 15);
			calculate_level();
			enemy_ai();
			game_over_ai();
			pause_game();
		
		} else if (state == game_over) {
			
			draw_hud();
			draw_player();
			draw_bases();
			draw_invaders();
			draw_saucer();
			draw_bullets(bullets, P_BULLETS);
			draw_bullets(e_bullets, E_BULLETS);
			draw_game_over();
		
		} else if (state == pause) {
			
			draw_hud();
			draw_player();
			draw_bases();
			draw_invaders();
			draw_saucer();
			draw_bullets(bullets, P_BULLETS);
			draw_bullets(e_bullets, E_BULLETS);
			pause_game();
		}

		/* Ask SDL to update the entire screen. */
		SDL_Flip(screen);

		next_game_tick += 1000 / 30;
		sleep = next_game_tick - SDL_GetTicks();
	
		if( sleep >= 0 ) {

            		SDL_Delay(sleep);
        	}
	}
	
	return 0;
}
