/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creator.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:03:46 by tlutz             #+#    #+#             */
/*   Updated: 2025/11/28 15:03:47 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "raycast.h"
#include "cub3D.h"

void	define_portal_segment(t_portal *portal)
{
	if (portal->facing == NORTH || portal->facing == SOUTH)
	{
		portal->segment_start.x = portal->world_x - PORTAL_HALF_WIDTH;
		portal->segment_start.y = portal->world_y;
		portal->segment_end.x = portal->world_x + PORTAL_HALF_WIDTH;
		portal->segment_end.y = portal->world_y;
	}
	else if (portal->facing == EAST || portal->facing == WEST)
	{
		portal->segment_start.x = portal->world_x;
		portal->segment_start.y = portal->world_y - PORTAL_HALF_WIDTH;
		portal->segment_end.x = portal->world_x;
		portal->segment_end.y = portal->world_y + PORTAL_HALF_WIDTH;
	}
}

void	create_portal_helper(t_ray *ray, t_portal *portal)
{
	if (ray->dir.y < 0)
	{
		portal->world_y = ray->map_tile.y + 1.0f;
		portal->graphical_facing = NORTH;
		portal->facing = SOUTH;
	}
	else
	{
		portal->world_y = (float)ray->map_tile.y;
		portal->graphical_facing = SOUTH;
		portal->facing = NORTH;
	}
	portal->world_x = ray->map_tile.x + 0.5f;
}

void	create_portal(t_ray *ray, t_portal *portal)
{
	portal->active = true;
	portal->map_x = ray->map_tile.x;
	portal->map_y = ray->map_tile.y;
	portal->side = ray->wall_tile_hit_side;
	if (ray->wall_tile_hit_side == HORIZONTAL_HIT)
	{
		if (ray->dir.x < 0)
		{
			portal->world_x = ray->map_tile.x + 1.0f;
			portal->graphical_facing = WEST;
			portal->facing = EAST;
		}
		else
		{
			portal->world_x = (float)ray->map_tile.x;
			portal->graphical_facing = EAST;
			portal->facing = WEST;
		}
		portal->world_y = ray->map_tile.y + 0.5f;
	}
	else if (ray->wall_tile_hit_side == VERTICAL_HIT)
		create_portal_helper(ray, portal);
}
