#include <stdlib.h>
#include "mapgen.h"
#include <time.h>
#include <stdio.h>

void rand_position_player(t_mapgen *cfg)
{
	srand(time(NULL));
	cfg->player_x = (rand() % (cfg->width - 2)) + 1;
	cfg->player_y = (rand() % (cfg->height - 2)) + 1;
	cfg->map[cfg->player_y][cfg->player_x] = 'P';
}

int random_direction(void)
{
	int dir = rand() % 4;
	if (dir == 0)
		return (N);
	else if (dir == 1)
		return (S);
	else if (dir == 2)
		return (E);
	else
		return (W);
}