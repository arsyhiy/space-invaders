#pragma once    // однократное подключение файла
#define BASE_WIDTH 60
#include "SDL.h"
#include "structure.h"
#include "init.h"

//Create damage to the base sprite for player and enemy bullet collisions
void bullet_base_damage(struct base_t *base, int b_num, struct bullet_t *bullet, int l) {

	int i;
	int x,y;
	SDL_Rect src;
	SDL_Rect dest;
				
	SDL_LockSurface(base_img[b_num]);
	Uint8 *raw_pixels;

	raw_pixels = (Uint8 *) base_img[b_num]->pixels;
	
	int pix_offset;

	//bottom
	if (l == 0) {
	
		//how far from the left did the bullet hit the base sprite
		x = (bullet->hitbox.x + 3) - base->hitbox.x;

		//start from bottom of the base sprite
		y = base->hitbox.h - 1;

		for(i = 0; i < base->hitbox.h; i++) {
		
			//the x calculation can get us to pixel column 60 when 59 is the maximum (0 - 59 is 60 pixels)
			if (x >= BASE_WIDTH) {
				x = BASE_WIDTH - 1;
			}

			pix_offset = y * base_img[b_num]->pitch  + x;	

			//found part part of the base sprite that is NOT magenta(index)
			//searching from the bottom up
			if (raw_pixels[pix_offset] != 227) {
					
				bullet->alive = 0;
				
				src.x = 0;
				src.y = 0;
				src.w = 11;
				src.h = 15;

				dest.x = x - 3;
				dest.y = y - 14;
				dest.w = 11;
				dest.h = 15;
 			
				SDL_UnlockSurface(base_img[b_num]);
				SDL_BlitSurface(damage_img, &src, base_img[b_num], &dest);
				
				break;
			}
			
			y--;
		}
	}
	
	//top
	if (l == 1) {

		//how far from the left did the bullet hit the base sprite
		x = (bullet->hitbox.x + 3) - base->hitbox.x;

		//start from top of the base sprite
		y = 0;
		
		for(i = 0; i < base->hitbox.h; i++) {
			
			//the x calculation can get us to pixel column 60 when 59 is the maximum (0 - 59 is 60 pixels)
			if (x >= BASE_WIDTH) {
				x = BASE_WIDTH - 1;
			}

			pix_offset = y * base_img[b_num]->pitch  + x;	
		
			//found part part of the base sprite that is NOT magenta(index)
			//searching from the top down
			if (raw_pixels[pix_offset] != 227) {
					
				bullet->alive = 0;
			
				src.x = 0;
				src.y = 0;
				src.w = 11;
				src.h = 15;

				dest.x = x - 3;
				dest.y = y;
				dest.w = 11;
				dest.h = 15;
				
				SDL_UnlockSurface(base_img[b_num]);
				SDL_BlitSurface(damage_top_img, &src, base_img[b_num], &dest);
				
				break;
			}
			
			y++;
		}
	}

	SDL_UnlockSurface(base_img[b_num]);
}


//Create damage to the base sprite for enemy and base collisions
void enemy_base_damage(struct enemy_t *enemy, struct base_t *base, int index) {
	
	int x,y;
	SDL_Rect dest;

	//the x hot spot is taken from the top left of the sprite with the speed in pixels
	//added ahead in case the enemy skips the last few pixels of the sprite and
	//the collision is no longer detected. Speed in pixels is subtracted if traveling left
	
	if (invaders.direction == right) {
	
		x = (enemy->hitbox.x + invaders.speed) - base->hitbox.x;
		y = enemy->hitbox.y - base->hitbox.y;
		
		if (x > 0) {
			
			dest.x = 0;
			dest.y = y;
			dest.w = x;
			dest.h = enemy->hitbox.h;
		
			SDL_FillRect(base_img[index], &dest, 227);
		}
	
	} else if (invaders.direction == left){
		
		x = (enemy->hitbox.x + (enemy->hitbox.w - 1)) - invaders.speed;
		x = x - base->hitbox.x;
		y = enemy->hitbox.y - base->hitbox.y;

		if (x < base->hitbox.w) {
		
			dest.x = x;
			dest.y = y;
			dest.w = base->hitbox.w - 1;
			dest.h = enemy->hitbox.h;
		
			SDL_FillRect(base_img[index], &dest, 227);
		}
	}		
}


