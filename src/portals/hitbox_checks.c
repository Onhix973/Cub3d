#include "structs.h"
#include "cub3D.h"
#include "raycast.h"

bool	check_for_portal(t_portal *portal, t_ray *ray)
{
	bool	is_portal_slice;

	is_portal_slice = false;
	if (portal->active && ray->map_tile.x == portal->map_x
		&& ray->map_tile.y == portal->map_y
		&& ray->wall_tile_hit_side == portal->side)
	{
		if (portal->side == HORIZONTAL_HIT)
		{
			if ((portal->graphical_facing == WEST && ray->dir.x < 0)
				|| (portal->graphical_facing == EAST && ray->dir.x > 0))
				is_portal_slice = true;
		}
		else if (portal->side == VERTICAL_HIT)
		{
			if ((portal->graphical_facing == NORTH && ray->dir.y < 0)
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

void	fill_rect_corners(t_vector *pos, t_vector rect_corners[4])
{
	const float	left = pos->x - (HITBOX_OFFSET + 0.1f);
	const float	right = pos->x + (HITBOX_OFFSET + 0.1f);
	const float	top = pos->y - (HITBOX_OFFSET + 0.1f);
	const float	bottom = pos->y + (HITBOX_OFFSET + 0.1f);

	rect_corners[0] = (t_vector){left, top};
	rect_corners[1] = (t_vector){right, top};
	rect_corners[2] = (t_vector){right, bottom};
	rect_corners[3] = (t_vector){left, bottom};
}

bool	player_hb_intersects_with_segment(t_vector *pos, t_portal *portal)
{
	t_vector	corners[2];
	t_vector	rect_corners[4];

	fill_rect_corners(pos, rect_corners);
	get_segment_side(portal, rect_corners, corners);
	if (is_point_on_segment(corners[0], portal->segment_start,
			portal->segment_end) && is_point_on_segment(corners[1],
			portal->segment_start, portal->segment_end))
		return (true);
	return (false);
}
