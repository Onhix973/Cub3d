#include "parsing.h"
#include <stdlib.h>

char **dup_map(const t_map *map)
{
	char **cpy;
	int	x;
	int y;

	cpy = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (cpy == NULL)
		return (NULL);
	y = 0;
	while (y < map->height)
	{
		cpy[y] = malloc(sizeof(char) * (map->width + 1));
		if (cpy[y] == NULL)
		{
			while (y > 0)
			{
				free(cpy[--y]);
			}
			free(cpy);
			return (NULL);
		}
		x = 0;
		while (x < map->width)
		{
			cpy[y][x] = map->grid[y][x];
			x++;
		}
		cpy[y][x] = '\0';
		y++;
	}
	cpy[y] = NULL;
	return (cpy);
}

void flood_fill(t_map *cpy_map, int y, int x,int *leak)
{
	if (*leak != 0)
		return ;
	if (x < 0 || x >= cpy_map->width
		|| y < 0 || y >= cpy_map->height)
	{
		*leak = 1;
		return ;
	}
	if (cpy_map->grid[y][x] == ' ')
	{
		*leak = 1;
		return ;
	}
	if (cpy_map->grid[y][x] != '0')
		return ;
	cpy_map->grid[y][x] = 'X';
	flood_fill(cpy_map, y + 1, x, leak);
	flood_fill(cpy_map, y - 1, x, leak);
	flood_fill(cpy_map, y, x + 1, leak);
	flood_fill(cpy_map, y, x - 1, leak);
}

int check_close(const t_map *map)
{
	t_map cpy_map;
	int leak;

	cpy_map.player_x = map->player_x;
	cpy_map.player_y = map->player_y;
	cpy_map.width = map->width;
	cpy_map.height = map->height;
	cpy_map.grid = dup_map(map);
	leak = 0;
	if (cpy_map.grid == NULL)
		return (write_error("Error: malloc failed\n"));
	flood_fill(&cpy_map, cpy_map.player_y, cpy_map.player_x, &leak);
	free_split(cpy_map.grid);
	if (leak == 1)
		return (write_error("Error: map not closed\n"));
	return (1);
}