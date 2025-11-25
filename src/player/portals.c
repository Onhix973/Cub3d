#include "structs.h"
#include "cub3D.h"
#include "raycast.h"

#include <stdio.h>
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
	printf("Portal segment is at : %f, %f | %f, %f\n", portal->segment_start.x, 
		portal->segment_start.y, portal->segment_end.x, portal->segment_end.y);
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
	printf("PORTAL CREATED AT : %f, %f\n", portal->world_x, portal->world_y);
}

bool	check_for_portal(t_portal *portal, t_ray *ray)
{
	bool	is_portal_slice;

	is_portal_slice = false;
	if (portal->active && ray->map_tile.x == portal->map_x \
	&& ray->map_tile.y == portal->map_y \
	&& ray->wall_tile_hit_side == portal->side)
	{
		if (portal->side == HORIZONTAL_HIT)
		{
			if ((portal->graphical_facing == WEST && ray->dir.x < 0)\
			|| (portal->graphical_facing == EAST && ray->dir.x > 0))
				is_portal_slice = true;
		}
		else if (portal->side == VERTICAL_HIT)
		{
			if ((portal->graphical_facing == NORTH && ray->dir.y < 0)\
			|| (portal->graphical_facing == SOUTH && ray->dir.y > 0))
				is_portal_slice = true;
		}
	}
	return (is_portal_slice);
}

bool	is_point_on_segment(t_vector point, t_vector seg_strt, t_vector seg_end)
{
	t_vector	delta;
	float		seg_length_sq;
	float		proj_param;
	t_vector	proj;
	float		dist_sq;

	delta = substract_vectors(seg_end, seg_strt);
	seg_length_sq = delta.x * delta.x + delta.y * delta.y;
	if (seg_length_sq == 0)
		return (false);
	proj_param = ((point.x - seg_strt.x) * delta.x + (point.y - seg_strt.y) 
	* delta.y) / seg_length_sq;
	if (proj_param < 0.0f || proj_param > 1.0f)
		return (false);
	proj.x = seg_strt.x + proj_param * delta.x;
	proj.y = seg_strt.y + proj_param * delta.y;
	dist_sq = (point.x - proj.x) * (point.x - proj.x) + (point.y - proj.y) 
	* (point.y - proj.y);
	return (dist_sq <= HITBOX_OFFSET);
}

static void	get_segment_side(t_portal *portal, const t_vector rect_corners[4], 
	t_vector corners[2])
{
	if (portal->facing == SOUTH)
	{
		corners[0] = rect_corners[0]; 
		corners[1] = rect_corners[1];
	}
	else if (portal->facing == NORTH)
	{
		corners[0] = rect_corners[2];
		corners[1] = rect_corners[3];
	}
	else if (portal->facing == EAST)
	{
		corners[0] = rect_corners[0];
		corners[1] = rect_corners[3];
	}
	else if (portal->facing == WEST)
	{
		corners[0] = rect_corners[1];
		corners[1] = rect_corners[2];
	}
}

bool	player_hb_intersects_with_segment(t_vector *pos, t_portal *portal)
{
	const float	left = pos->x - (HITBOX_OFFSET + 0.1f);
	const float	right = pos->x + (HITBOX_OFFSET + 0.1f);
	const float	top = pos->y - (HITBOX_OFFSET + 0.1f);
	const float	bottom = pos->y + (HITBOX_OFFSET + 0.1f);
	t_vector	corners[2];
	const t_vector	rect_corners[4] = 
	{
		{left, top},
		{right, top},
		{right, bottom},
		{left,bottom}
	};
	get_segment_side(portal, rect_corners, corners);
	if (is_point_on_segment(corners[0], portal->segment_start, portal->segment_end)
	&& is_point_on_segment(corners[1], portal->segment_start, portal->segment_end))
		return (true);
	return (false);
}
