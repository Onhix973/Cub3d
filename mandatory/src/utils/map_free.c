/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:53:25 by abonifac          #+#    #+#             */
/*   Updated: 2025/11/28 15:53:26 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

void	map_free(t_map *m)
{
	int	i;

	if (m->grid == NULL)
		return ;
	i = 0;
	while (m->grid[i] != NULL && i < m->height)
	{
		free(m->grid[i]);
		i++;
	}
	free(m->grid);
	map_init(m);
}
