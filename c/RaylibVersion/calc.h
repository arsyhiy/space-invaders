#include "init.h"
#include "time.h"

//Determine game level
void calculate_level() {

	if (invaders.killed != 0 && invaders.killed % 50 == 0) {
		
		score.level++;
		init_invaders();
		init_bases();
		init_saucer();
		pause_for(500);
	}
}
