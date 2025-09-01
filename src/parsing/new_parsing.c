#include "parsing.h"
#include <stdlib.h>
#include "libft.h"

void	free_split(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	confid_init(t_config *c)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		c->path[i] = NULL;
		i++;
	}
	i = 0;
	while (i < NB_OF_MAP_PARAMS)
	{
		c->seen[i] = 0;
		i++;
	}
	i = 0;
	while (i < 3)
	{
		c->floor[i] = 0;
		c->ceil[i] = 0;
		i++;
	}
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

void ctx_init(t_context *ctx)
{
	confid_init(&ctx->conf);
	map_init(&ctx->map);
	ctx->lines = NULL;
}

void config_free(t_config *c)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (c->path[i] != NULL)
			free(c->path[i]);
		i++;
	}
}

void map_free(t_map *m)
{
	int i;

	if (m->grid == NULL)
		return ;
	i = 0;
	while (i < m->height)
	{
		if (m->grid[i] != NULL)
			free(m->grid[i]);
		i++;
	}
	free(m->grid);
	map_init(m);
}

void context_free(t_context *ctx)
{
	map_free(&ctx->map);
	config_free(&ctx->conf);
	ft_free_split(ctx->lines);
	ctx->lines = NULL;
}