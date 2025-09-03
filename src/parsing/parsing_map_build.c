#include "parsing.h"
#include <stdlib.h>
#include "libft.h"

int get_dims(char **lines, int *width, int *height)
{
	int w;
	int h;
	int i;
	int line_len;

	if (lines == NULL || *lines == NULL)
		return (write_error("Error: empty map\n"));
	w = 0;
	h = 0;
	i = 0;
	while (lines[i])
	{
		line_len = ft_strlen(lines[i]);
		if (line_len > w)
			w = line_len;
		h++;
		i++;
	}
	*width = w;
	*height = h;
	if (w == 0 || h == 0)
		return (0);
	return (1);
}

void replace_player(t_map *map)
{
	map->grid[map->player_y][map->player_x] = '0';
}

int rect_map(char **map_lines, t_map *map)
{
	int i;
	int j;
	int line_len;

	if (get_dims(map_lines, &map->width, &map->height) == 0)
		return (write_error("Error: empty map\n"));
	map->grid = (char **)malloc(sizeof(char *) * (map->height + 1));
	map->grid[map->height] = NULL;
	if (map->grid == NULL)
		return (write_error("Error: malloc failed\n"));
	i = 0;
	while (map_lines[i])
	{
		line_len = ft_strlen(map->grid[i]);
		if (line_len < map->width)
		{
			map->grid[i] = malloc(sizeof(char) * (map->width + 1));
			if (map->grid[i] == NULL)
			{
				map_free(map);
				return (write_error("Error: malloc failed\n"));
			}
			ft_memset(map->grid[i], ' ', map->width);
			map->grid[i][map->width] = '\0';
			j = 0;
			while (map_lines[i][j])
			{
				if (map_lines[i][j] == ' ')
				{
					j++;
					continue ;
				}
				map->grid[i][j] = map_lines[i][j];
				j++;
			}
		}
		i++;
	}
	replace_player(map);
	return (1);
}
