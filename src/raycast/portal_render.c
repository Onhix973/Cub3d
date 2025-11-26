#include "structs.h"
#include "raycast.h"
#include "cub3D.h"
#include <math.h>

void	init_ray_step_and_dist_tp(t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->tile_step.x = -1;
		ray->dist_next_hgrid = (ray->origin.x - ray->map_tile.x) \
		* ray->delta_dist.x;
	}
	else
	{
		ray->tile_step.x = 1;
		ray->dist_next_hgrid = (ray->map_tile.x + 1.0 - ray->origin.x) \
		* ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->tile_step.y = -1;
		ray->dist_next_vgrid = (ray->origin.y - ray->map_tile.y) \
		* ray->delta_dist.y;
	}
	else
	{
		ray->tile_step.y = 1;
		ray->dist_next_vgrid = (ray->map_tile.y + 1.0 - ray->origin.y) \
		* ray->delta_dist.y;
	}
}

void	transform_ray_through_portal(t_ray *ray, t_portal *in, t_portal *out)
{
	t_vector	in_dir;
	t_vector	out_dir;
	t_vector	relative_pos;
	float		angle;

	facing_to_vector(in->facing, &in_dir);
	facing_to_vector(out->facing, &out_dir);
	in_dir.x = -in_dir.x;
	in_dir.y = -in_dir.y;
	relative_pos.x = ray->pos.x - in->world_x;
	relative_pos.y = ray->pos.y - in->world_y;
	angle = compute_rotation_angle(&in_dir, &out_dir);
	rotate_vector(&relative_pos, angle);
	ray->pos.x = out->world_x + relative_pos.x;
	ray->pos.y = out->world_y + relative_pos.y;
	rotate_dvector(&ray->dir, angle);
	ray->origin.x = ray->pos.x;
	ray->origin.y = ray->pos.y;
	ray->map_tile.x = (int)ray->pos.x;
	ray->map_tile.y = (int)ray->pos.y;
	ray->delta_dist.x = fabs(1.0 / ray->dir.x);
	ray->delta_dist.y = fabs(1.0 / ray->dir.y);
	init_ray_step_and_dist_tp(ray);
}
