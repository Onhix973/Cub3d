/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player_dir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:17:02 by abonifac          #+#    #+#             */
/*   Updated: 2025/09/12 14:17:32 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapgen.h"

void	update_player_direction(t_mapgen *cfg)
{
	if (cfg->map[cfg->player_y + 1][cfg->player_x] == '0')
		cfg->map[cfg->player_y][cfg->player_x] = 'S';
	else if (cfg->map[cfg->player_y - 1][cfg->player_x] == '0')
		cfg->map[cfg->player_y][cfg->player_x] = 'N';
	else if (cfg->map[cfg->player_y][cfg->player_x + 1] == '0')
		cfg->map[cfg->player_y][cfg->player_x] = 'E';
	else if (cfg->map[cfg->player_y][cfg->player_x - 1] == '0')
		cfg->map[cfg->player_y][cfg->player_x] = 'W';
}
