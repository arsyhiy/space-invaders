#pragma once    // однократное подключение файла
#include "SDL.h"
#include "init.h"
#include "damage.h"
#include "time.h"

struct bullet_t bullets[P_BULLETS];
struct bullet_t e_bullets[E_BULLETS];


//Detect any collision between any two non rotated rectangles
int collision(SDL_Rect a, SDL_Rect b) {

	if (a.y + a.h < b.y) {
	
		return 0;
	}
				
	if (a.y > b.y + b.h) {
					
		return 0;
	}
				
	if (a.x > b.x + b.w) {
					
		return 0;
	}
			
	if (a.x + a.w < b.x) {
					
		return 0;
	}

	return 1;
}


//Look for collisions based on enemy and base rectangles
void enemy_base_collision() {

	int i,j,k,c;

	for (i = 0; i < 5; i++) {

		for (j = 0;  j < 10; j++) {
		
			for (k = 0;  k < BASE; k++) {
			
				if (invaders.enemy[i][j].alive == 1) {
				
					c = collision(invaders.enemy[i][j].hitbox,base[k].hitbox);		
					
					if (c == 1) {
						
						enemy_base_damage(&invaders.enemy[i][j], &base[k], k);
					}
				}
			}
		}
	}
}

//Look for collisions based on player bullet and invader rectangles
void enemy_hit_collision() {

	int i,j,k,c;
	
	for (i = 0; i < 5; i++) {
		
		for (j = 0; j < 10; j++) {
			
			if (invaders.enemy[i][j].alive == 1) {
			
				for (k = 0; k < P_BULLETS; k++) {
			
					if (bullets[k].alive == 1) {
						
						c = collision(bullets[k].hitbox, invaders.enemy[i][j].hitbox);
				
						if (c == 1) {
				
							invaders.enemy[i][j].alive = 0;
							bullets[k].alive = 0;
							bullets[k].hitbox.x = 0;
							bullets[k].hitbox.y = 0;
							invaders.killed++;
							score.points += invaders.enemy[i][j].points;
						}
					}
				}
			}
		}
	}
}

//Look for collisions based on enemy bullet and player rectangles
void player_hit_collision() {

	int i,c;

	for(i = 0; i < E_BULLETS; i++) {
	
		if (e_bullets[i].alive == 1) {

			c = collision(e_bullets[i].hitbox, player.hitbox);

			if (c == 1) {
				
				if (player.lives >= 0) {
				
					player.lives--;
					pause_for(500);
				}
			}
		}
	}
}

//Look for collisions based on player bullet and saucer rectangles
void saucer_hit_collision() {

	int i,c;

	if (saucer.alive == 1) {
	
		for(i = 0; i < P_BULLETS; i++) {
	
			if (bullets[i].alive == 1) {
			
				c = collision(bullets[i].hitbox, saucer.hitbox);
	
				if (c == 1) {
				
					int r = rand() % 3;
					
					switch (r) {
			
						case 0:
							score.points += 50;
							break;
	
						case 1:
							score.points += 150;
							break;
	
						case 2:
							score.points += 300;
							break;
	
						default:
							break;
					}
					
					//sucer was hit reset for next time
					saucer.alive = 0;
					
					if (saucer.direction == left) {
						
						saucer.hitbox.x = 0; 
						saucer.direction = right; 
	
					} else if (saucer.direction == right) {
					
						saucer.hitbox.x = WIDTH - saucer.hitbox.w; 
						saucer.direction = left; 
					}
				}
			}
		}
	}
}

//Look for collisions based on invader and player rectangles
int enemy_player_collision() {

	int i,j,c;

	for(i = 0; i < 5; i++) {

		for(j = 0; j < 10; j++) {
		
			if (invaders.enemy[i][j].alive == 1) {
					
				c = collision(player.hitbox, invaders.enemy[i][j].hitbox);

				if (c == 1) {
				
					player.lives--;
					pause_for(500);
					init_invaders();
					init_bases();
					return 1;
				}
			}
		}
	}

	return 0;
}

//Look for collisions based on bullet and base rectangles
void bullet_base_collision(struct bullet_t b[], int max, int l) {

	int i,j,c;

	for (i = 0; i < max; i++) {
		
		for (j = 0; j < BASE; j++) {
	
			if (b[i].alive == 1) {
			
				c = collision(b[i].hitbox, base[j].hitbox);

				if (c == 1) {
					
					bullet_base_damage(&base[j], j, &b[i],l);
				}
			}
		}
	}
}
