#include "parsing.h"
#include <stdlib.h>

void	map_free(t_map *m)
{
	int	i;

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
