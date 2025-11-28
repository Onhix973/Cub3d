/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:30:00 by abonifac          #+#    #+#             */
/*   Updated: 2025/11/28 15:08:04 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mapgen.h"
#include <time.h>
#include <stdio.h>

void	rand_position_player(t_mapgen *cfg)
{
	srand(time(NULL));
	cfg->player_x = (rand() % (cfg->width - 2)) + 1;
	cfg->player_y = (rand() % (cfg->height - 2)) + 1;
}

void	set_direction(t_rand_dir *rd, t_mapgen cfg)
{
	if (rd->new_x != cfg.player_x)
	{
		if (rd->new_x > cfg.player_x)
			rd->direction = E;
		else
			rd->direction = W;
	}
	else
	{
		if (rd->new_y > cfg.player_y)
			rd->direction = S;
		else
			rd->direction = N;
	}
}

void	put_weight(t_rand_dir *rd, t_mapgen *cfg)
{
	set_direction(rd, *cfg);
	rd->k = 0;
	rd->weight = 0;
	if (cfg->map[rd->new_y][rd->new_x] != BORDER_W)
	{
		rd->weight = 1;
		if (cfg->map[rd->new_y][rd->new_x] == '1')
			rd->weight = 8;
		while (rd->k < rd->weight)
		{
			rd->dice[rd->count] = rd->direction;
			rd->k++;
			rd->count++;
		}
	}
}

int	biased_rand_dir(t_mapgen *cfg, int px, int py)
{
	t_rand_dir	rd;

	init_rand_dir(&rd);
	rd.new_x = px;
	rd.new_y = py - 1;
	put_weight(&rd, cfg);
	rd.new_y = py + 1;
	put_weight(&rd, cfg);
	rd.new_y = py;
	rd.new_x = px - 1;
	put_weight(&rd, cfg);
	rd.new_x = px + 1;
	put_weight(&rd, cfg);
	if (rd.count == 0)
		return (0);
	return (rd.dice[rand() % rd.count]);
}
