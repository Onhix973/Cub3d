#include "mapgen.h"

void border_walls(t_mapgen *cfg, char c)
{
	int i;

	i = 0;
	while (i < cfg->width)
	{
		cfg->map[0][i] = c;
		cfg->map[cfg->height - 1][i] = c;
		i++;
	}
	i = 0;
	while (i < cfg->height)
	{
		cfg->map[i][0] = c;
		cfg->map[i][cfg->width - 1] = c;
		i++;
	}
}