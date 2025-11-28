/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:30:56 by abonifac          #+#    #+#             */
/*   Updated: 2025/11/27 16:39:24 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapgen.h"
#include <stdlib.h>
#include "libft.h"

void	init_config(t_mapgen *config)
{
	config->map = NULL;
	config->width = 0;
	config->height = 0;
	config->player_x = -1;
	config->player_y = -1;
	config->area = 0;
}

void	init_rand_dir(t_rand_dir *rd)
{
	rd->count = 0;
	rd->weight = 0;
	rd->k = 0;
	rd->new_x = 0;
	rd->new_y = 0;
	rd->direction = 0;
	ft_memset(rd->dice, 0, sizeof(int) * DICE_SIZE);
}
