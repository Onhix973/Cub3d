#include "parsing.h"
#include <stdlib.h>

void	config_init(t_config *c)
{
	int	i;

	i = -1;
	while (++i < 4)
		c->path[i] = NULL;
	i = -1;
	while (++i < NB_OF_MAP_PARAMS)
		c->seen[i] = 0;
	i = -1;
	while (++i < 3)
	{
		c->floor[i] = 0;
		c->ceil[i] = 0;
	}
	c->i_map_start = -1;
	c->floor_hex = 0;
	c->ceil_hex = 0;
}

void	map_init(t_map *m)
{
	m->grid = NULL;
	m->width = 0;
	m->height = 0;
	m->player_x = -1;
	m->player_y = -1;
	m->player_dir = 0;
}

void	ctx_init(t_context *ctx)
{
	config_init(&ctx->conf);
	map_init(&ctx->map);
	ctx->lines = NULL;
}
