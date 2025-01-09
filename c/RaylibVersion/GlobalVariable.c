#include "structure.h"

#define BASE 4
#define BASE_WIDTH 60
#define BASE_HEIGHT 40
#define P_BULLETS 1
#define E_BULLETS 3
#define E_WIDTH 30


struct invaders_t invaders;
struct score_t score;
struct player_t player;
struct saucer_t saucer;
struct base_t base[BASE];
struct bullet_t e_bullets[E_BULLETS];


enum state_t {menu, options, game, game_over, pause};
enum state_t state;
