#include "init.h"
struct bullet_t e_bullets[E_BULLETS];

//Determine for game over event
void game_over_ai() {
	
	if (player.lives < 0) {
		
		state = game_over;
	}
}


//Determine when saucer should appear
void saucer_ai() {

	//every 20 shots
	if (score.shots != 0 && score.shots % 20 == 0) {
	
		saucer.alive = 1;
	}
}


//Determine when invaders should shoot
void enemy_ai() {

	int i, j, k;

	for (i = 0; i < 10; i++) {
		
		for (j = 4; j >= 0; j--) {
			
			if (invaders.enemy[j][i].alive == 1) {
				
				//player
				int mid_point = player.hitbox.x + (player.hitbox.w / 2);
				
				//enemy
				int start = invaders.enemy[j][i].hitbox.x;
				int end = invaders.enemy[j][i].hitbox.x + invaders.enemy[j][i].hitbox.w;

				if (mid_point > start && mid_point < end) {

					//fire bullet if available
					for (k = 0; k < E_BULLETS; k++) {
			
						if (e_bullets[k].alive == 0) {
				
							int r = rand() % 30;

							if (r == 1) {
								e_bullets[k].hitbox.x = start + (E_WIDTH / 2) ;
								e_bullets[k].hitbox.y = invaders.enemy[j][i].hitbox.y;
								e_bullets[k].alive = 1;
							}

							break;
						}
					}
				}
				
				//alive enemy found reversing up the enemy grid dont check the rest of the colum
				break;
			}
		}
	}
}
