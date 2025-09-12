/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   border_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:19:10 by abonifac          #+#    #+#             */
/*   Updated: 2025/09/12 14:19:28 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapgen.h"

void	border_walls(t_mapgen *cfg, char c)
{
	int	i;

	i = 0;
	while (i < cfg->width)
	{
		cfg->map[0][i] = c;
		cfg->map[cfg->height - 1][i] = c;
		i++;
	}
	i = 0;
	while (i < cfg->height)
	{
		cfg->map[i][0] = c;
		cfg->map[i][cfg->width - 1] = c;
		i++;
	}
}
