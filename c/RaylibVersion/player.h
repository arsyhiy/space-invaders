#include "structure.h"
#include "init.h"


struct bullet_t bullets[P_BULLETS];


//Shoot bullet/s from player
void player_shoot() {

	int i;
	
	for (i = 0; i < P_BULLETS; i++) {
				
		if (bullets[i].alive == 0) {
			
			//count number of shots fired
			score.shots++;

			bullets[i].hitbox.x = player.hitbox.x + (P_WIDTH / 2);
			//-5 at the end so the bullets ends closer to the top of the screen due to 30px speed
			bullets[i].hitbox.y = player.hitbox.y - (bullets[i].hitbox.h + 10);
			bullets[i].alive = 1;
			break;
		}
	}
}


