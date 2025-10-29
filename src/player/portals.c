#include "structs.h"
#include "cub3D.h"
#include "raycast.h"

#include <stdio.h>

bool	segment_intersect(t_vector first_seg_start, t_vector first_seg_end, t_vector second_seg_start, t_vector second_seg_end)
{
	t_vector	first_delta;
	t_vector	second_delta;
	float	denominator;
	float	s;
	float	t;

	first_delta.x = first_seg_end.x - first_seg_start.x;
	first_delta.y = first_seg_end.y - first_seg_start.y;
	second_delta.x = second_seg_end.x - second_seg_start.x;
	second_delta.y = second_seg_end.y - second_seg_start.y;
	denominator = (-second_delta.x * first_delta.y + first_delta.x * second_delta.y);
	if (denominator == 0.0f)
		return (false);
	s = (-first_delta.y * (first_seg_start.x - second_seg_start.x) + first_delta.x * (first_seg_start.y - second_seg_start.y)) / denominator;
	t = (second_delta.x * (first_seg_start.y - second_seg_start.y) + second_delta.y * (second_seg_start.x - first_seg_start.x)) / denominator;
	return (s >= 0.0f && s <= 1.0f && t >= 0.0f && t <= 1.0f);
}

bool	is_point_in_rectangle(t_vector *point, t_vector *rect, float rect_width, float rect_height)
{
	return (point->x >= rect->x && point->x <= rect->x + rect_width \
		&& point->y >= rect->y && point->y <= rect->y + rect_height);
}

void	define_portal_segment(t_portal *portal)
{
	float	half_width;

	half_width = PORTAL_WIDTH / 2.0f;
	if (portal->facing == NORTH || portal->facing == SOUTH)
	{
		portal->segment_start.x = portal->world_x - half_width;
		portal->segment_start.y = portal->world_y;
		portal->segment_end.x = portal->world_x + half_width;
		portal->segment_end.y = portal->world_y;
	}
	else if (portal->facing == EAST || portal->facing == WEST)
	{
		portal->segment_start.x = portal->world_x;
		portal->segment_start.y = portal->world_y - half_width;
		portal->segment_end.x = portal->world_x;
		portal->segment_end.y = portal->world_y + half_width;
	}
}

void	create_portal(t_data *game, t_ray *ray, t_hit *hit, t_portal *portal)
{
	portal->active = true;
	portal->map_x = ray->map_tile.x;
	portal->map_y = ray->map_tile.y;
	portal->side = hit->wall_tile_hit_side;
	if (hit->wall_tile_hit_side == HORIZONTAL_HIT)
	{
		if (ray->dir_x < 0)
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
		portal->world_y = game->player->pos.y + ray->dir_y * hit->proj_wall_hit_dist;
	}
	else if (hit->wall_tile_hit_side == VERTICAL_HIT)
	{
		if (ray->dir_y < 0)
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
		portal->world_x = game->player->pos.x + ray->dir_x * hit->proj_wall_hit_dist;
	}
}

bool	check_for_portal(t_portal *portal, t_ray *ray, t_hit *hit_data)
{
	bool	is_portal_slice;

	is_portal_slice = false;
	if (portal->active && ray->map_tile.x == portal->map_x \
	&& ray->map_tile.y == portal->map_y \
	&& hit_data->wall_tile_hit_side == portal->side)
	{
		if (portal->side == HORIZONTAL_HIT)
		{
			if ((portal->graphical_facing == WEST && ray->dir_x < 0)\
			|| (portal->graphical_facing == EAST && ray->dir_x > 0))
				is_portal_slice = true;
		}
		else if (portal->side == VERTICAL_HIT)
		{
			if ((portal->graphical_facing == NORTH && ray->dir_y < 0)\
			|| (portal->graphical_facing == SOUTH && ray->dir_y > 0))
				is_portal_slice = true;
		}
	}
	return (is_portal_slice);
}

bool	player_hb_intersects_with_segment(t_player *player, t_portal *portal)
{
	const float	left = player->pos.x - (HITBOX_OFFSET + 0.1f);
	const float	right = player->pos.x + (HITBOX_OFFSET + 0.1f);
	const float	top = player->pos.y - (HITBOX_OFFSET + 0.1f);
	const float	bottom = player->pos.y + (HITBOX_OFFSET + 0.1f);
	t_vector	edge_start;
	t_vector	edge_end;
	t_vector	mid_point;
	const t_vector	rect_corners[4] = 
	{
		{left, top},
		{right, top},
		{right, bottom},
		{left,bottom}
	};
	int	i = 0;
	while (i < 4)
	{
		edge_start = rect_corners[i];
		edge_end = rect_corners[(i + 1) % 4];
		if (segment_intersect(edge_start, edge_end, portal->segment_start, portal->segment_end))
			return (true);
		i++;
	}
	mid_point.x = (portal->segment_start.x + portal->segment_end.x) * 0.5f;
	mid_point.y = (portal->segment_start.y + portal->segment_end.y) * 0.5f;
	if (mid_point.x >= left && mid_point.x <= right && mid_point.y >= top && mid_point.y <= bottom)
		return (true);
	return (false);
}
