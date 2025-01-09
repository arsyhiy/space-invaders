#include "structure.h"
#define HEIGHT 600 
#define WIDTH 600
#define E_WIDTH 30

extern struct invaders_t invaders;
extern struct saucer_t saucer;
extern struct player_t player;

//Set invader movment speed
void set_invaders_speed();


//Move positions of both enemy and player bullets on screen
int move_bullets(struct bullet_t b[], int max, int speed);

//Move invaders down one space once the reach the edge
void move_invaders_down();

//Move invaders based on there current direction
int move_invaders(int speed); 

//Move player left or right
void move_player(enum direction_t direction);

//Move saucer based on there current direction
void move_saucer();
