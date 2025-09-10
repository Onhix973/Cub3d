#include <stdlib.h>
#include "mapgen.h"
#include <time.h>

void rand_position_player(t_mapgen *cfg)
{
	srand(time(NULL));
	cfg->player_x = (rand() % (cfg->width - 2)) + 1;
	cfg->player_y = (rand() % (cfg->height - 2)) + 1;
	cfg->map[cfg->player_y][cfg->player_x] = 'P';
}