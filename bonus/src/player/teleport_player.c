/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teleport_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:03:43 by tlutz             #+#    #+#             */
/*   Updated: 2025/11/28 15:03:44 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <structs.h>
#include "cub3D.h"
#include "raycast.h"
#include <math.h>

void	facing_to_vector(t_facing face, t_vector *vector)
{
	if (face == NORTH)
	{
		vector->x = 0.0f;
		vector->y = -1.0f;
	}
	else if (face == SOUTH)
	{
		vector->x = 0.0f;
		vector->y = 1.0f;
	}
	else if (face == EAST)
	{
		vector->x = 1.0f;
		vector->y = 0.0f;
	}
	else if (face == WEST)
	{
		vector->x = -1.0f;
		vector->y = 0.0f;
	}
}

static float	get_dot_with_curr_pos(t_player *player, t_portal *portal,
	t_vector normal)
{
	t_vector	curr;

	curr.x = player->pos.x - portal->world_x;
	curr.y = player->pos.y - portal->world_y;
	return (dot_product(curr, normal));
}

static float	get_dot_with_prev_pos(t_player *player, t_portal *portal,
	t_vector normal)
{
	t_vector	prev;

	prev.x = player->prev_pos.x - portal->world_x;
	prev.y = player->prev_pos.y - portal->world_y;
	return (dot_product(prev, normal));
}

bool	did_cross_portal(t_player *player, t_portal *portal)
{
	t_vector	normal;
	t_vector	tangent;
	float		lateral_distance;
	float		dot_curr;
	float		dot_prev;

	facing_to_vector(portal->facing, &normal);
	dot_curr = get_dot_with_curr_pos(player, portal, normal);
	dot_prev = get_dot_with_prev_pos(player, portal, normal);
	if (dot_prev > 0.0f && dot_curr <= 0.0f)
	{
		tangent.x = -normal.y;
		tangent.y = normal.x;
		lateral_distance = fabsf(get_dot_with_curr_pos(player,
					portal, tangent));
		if (lateral_distance < PORTAL_HALF_WIDTH)
			return (true);
	}
	return (false);
}

//TODO
void	teleport_player_crossing_portal(t_data *game)
{
	if (!game->portals.linked)
		return ;
	if (did_cross_portal(game->player, &game->portals.a))
		teleport_to_portal(&game->portals.a, &game->portals.b, game->player);
	else if (did_cross_portal(game->player, &game->portals.b))
		teleport_to_portal(&game->portals.b, &game->portals.a, game->player);
}
