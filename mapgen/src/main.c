#include "libft.h"
#include "parsing.h"
#include "mapgen.h"
#include <stdio.h>


int create_map(t_mapgen *cfg)
{
	cfg->map = malloc(sizeof(char *) * (cfg->height + 1));
	if (cfg->map == NULL)
		return (write_error(MALLOC_ERR));
	cfg->map[cfg->height] = NULL;
	int i = 0;
	while (i < cfg->height)
	{
		cfg->map[i] = calloc(sizeof(char), cfg->width + 1);
		if (cfg->map[i] == NULL)
		{
			free_split(cfg->map);
			return (write_error(MALLOC_ERR));
		}
		ft_memset(cfg->map[i], '1', cfg->width);
		i++;
	}
	return (1);
}

int map_gen(t_mapgen *config)
{
	if (create_map(config) == 0)
		return (0);
	border_walls(config, '2');
	rand_position_player(config);
	config->area = (config->width - 2) * (config->height - 2);
	int i = 0;
	int target = config->area * 60 / 100;
	while (i < target)
	{
		int dir = random_direction();
		int x = config->player_x;
		int y = config->player_y;
		if (dir == N)
			y--;
		else if (dir == S)
			y++;
		else if (dir == E)
			x++;
		else if (dir == W)
			x--;
		if (config->map[y][x] == '2')
			continue ;
		if (config->map[y][x] == '1')
		{
			config->map[y][x] = '0';
			i++;
		}
		config->player_x = x;
		config->player_y = y;
	}
	border_walls(config, '1');
	return (1);
}

int	convert_args(char **av, t_mapgen *config)
{
	config->width = ft_atoi(av[1]);
	config->height = ft_atoi(av[2]);
	if (config->width <= 0 || config->height <= 0)
	{
		return (write_error("Width and height must be positive integers\n"));
	}
	return (1);
}

int main(int ac, char **av)
{
	t_mapgen config;
	if (ac != 3)
		return (write_error("Format is ./program <width> <height>\n"));
	init_config(&config);
	if (!convert_args(av, &config))
		return (1);
	if (!map_gen(&config))
		return (2);
	print_map(config.map);
	free_split(config.map);
	return (0);
}