#include "structs.h"
#include <stdlib.h>

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	if (tab && !*tab)
	{
		free(tab);
		return ;
	}
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return ;
}

void config_free(t_config *c)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (c->path[i] != NULL)
			free(c->path[i]);
		c->path[i] = NULL;
		i++;
	}
}

void context_free(t_context *ctx, bool free_map)
{
	if (free_map)
		map_free(&ctx->map);
	config_free(&ctx->conf);
	free_split(ctx->lines);
	ctx->lines = NULL;
}