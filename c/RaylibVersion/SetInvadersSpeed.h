#include "structure.h"

#define BASE 4
#define BASE_WIDTH 60
#define BASE_HEIGHT 40
#define P_BULLETS 1
#define E_BULLETS 3
#define E_WIDTH 30


extern struct invaders_t invaders;

//Set invader movment speed
void set_invaders_speed() {

	switch (invaders.killed) {
		
		case 10:

			invaders.speed = 2;
			invaders.state_speed = 800;
			break;
		
		case 20:

			invaders.speed = 4;
			invaders.state_speed = 600;
			break;
		
		case 30:

			invaders.speed = 8;
			invaders.state_speed = 200;
			break;
		
		case 40:

			invaders.speed = 16;
			invaders.state_speed = 0;
			break;
	}
}


