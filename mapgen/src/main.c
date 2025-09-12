/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:00:55 by abonifac          #+#    #+#             */
/*   Updated: 2025/09/12 14:59:29 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "mapgen.h"
#include <stdio.h>

int	create_map(t_mapgen *cfg)
{
	int	i;

	cfg->map = malloc(sizeof(char *) * (cfg->height + 1));
	if (cfg->map == NULL)
		return (write_error(MALLOC_ERR));
	cfg->map[cfg->height] = NULL;
	i = 0;
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

int	move_player(t_mapgen *cfg, int direction, int *i)
{
	int	x;
	int	y;

	x = cfg->player_x;
	y = cfg->player_y;
	if (direction == N)
		y--;
	else if (direction == S)
		y++;
	else if (direction == E)
		x++;
	else if (direction == W)
		x--;
	if (cfg->map[y][x] == '2')
		return (0);
	if (cfg->map[y][x] == '1')
	{
		cfg->map[y][x] = '0';
		(*i)++;
	}
	cfg->player_x = x;
	cfg->player_y = y;
	return (1);
}

void	map_gen_helper(t_mapgen *config)
{
	int	i;
	int	target;
	int	dir;

	i = 0;
	target = config->area * 60 / 100;
	while (i < target)
	{
		dir = biased_rand_dir(config, config->player_x, config->player_y);
		move_player(config, dir, &i);
		if (rand() % 100 < 80)
			if (!move_player(config, dir, &i))
				continue ;
		if (rand() % 100 < 60)
			if (!move_player(config, dir, &i))
				continue ;
		if (rand() % 100 < 40)
			if (!move_player(config, dir, &i))
				continue ;
	}
}

int	map_gen(t_mapgen *config)
{
	if (create_map(config) == 0)
		return (0);
	border_walls(config, '2');
	rand_position_player(config);
	config->area = (config->width - 2) * (config->height - 2);
	map_gen_helper(config);
	border_walls(config, '1');
	return (1);
}

int	main(int ac, char **av)
{
	t_mapgen	config;

	printf("NO textures/Asset-10.xpm\n");
	printf("SO textures/Asset-14.xpm\n");
	printf("WE textures/Asset-16_1.xpm\n");
	printf("EA textures/Asset-17_1.xpm\n");
	printf("C 50,100,200\n");
	printf("F 30,20,20\n");
	if (ac != 3 && ac != 1)
		return (write_error("Format is ./program <width> <height>\n"));
	init_config(&config);
	if (!convert_args(av, ac, &config))
		return (1);
	if (!map_gen(&config))
		return (2);
	update_player_direction(&config);
	print_map(config.map);
	free_split(config.map);
	return (0);
}
