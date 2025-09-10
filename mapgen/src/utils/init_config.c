#include "mapgen.h"
#include <stdlib.h>

void init_config(t_mapgen *config)
{
	config->map = NULL;
	config->width = 0;
	config->height = 0;
	config->player_x = -1;
	config->player_y = -1;
	config->area = 0;
}