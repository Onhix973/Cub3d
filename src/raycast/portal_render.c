#include "structs.h"
#include "raycast.h"
#include "cub3D.h"
#include <math.h>

void	update_ray_step_and_dist(t_ray *ray)
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

//TODO
#include <stdio.h>
void	update_ray(t_ray *ray, t_player *player)
{
	(void)player;
	ray->map_tile.x = (int)player->pos.x;
	ray->map_tile.y = (int)player->pos.y;
	ray->delta_dist.x = fabs(1.0 / ray->dir.x);
	ray->delta_dist.y = fabs(1.0 / ray->dir.y);
	ray->cos_view_angle = ray->dir.x * player->dir.x + ray->dir.y \
	* player->dir.y;
	update_ray_step_and_dist(ray);
}

void	setup_portal_camera(t_portal *in, t_portal *out, t_player *player)
{
	t_vector	in_facing_vec;
	t_vector	out_facing_vec;
	t_vector	in_dir;
	t_vector	relative_pos;
	float		angle;

	out->virtual_cam = player;
	relative_pos.x = player->pos.x - in->world_x;
	relative_pos.y = player->pos.y - in->world_y;
	facing_to_vector(in->facing, &in_facing_vec);
	facing_to_vector(out->facing, &out_facing_vec);
	in_dir.x = -in_facing_vec.x;
	in_dir.y = -in_facing_vec.y;
	angle = compute_rotation_angle(&in_dir, &out_facing_vec);
	rotate_vector(&relative_pos, angle);
	rotate_vector(&out->virtual_cam->dir, angle);
	rotate_vector(&out->virtual_cam->camera_plane, angle);
	out->virtual_cam->pos.x = out->world_x + relative_pos.x;
	out->virtual_cam->pos.y = out->world_y + relative_pos.y;
}

void	teleport_ray(t_ray *ray, t_portal *in, t_portal *out)
{
	t_vector	in_facing_vec;
	t_vector	out_facing_vec;
	t_vector	in_dir;
	t_vector	relative_pos;
	float		angle;

	relative_pos.x = ray->pos.x - in->world_x;
	relative_pos.y = ray->pos.y - in->world_y;
	facing_to_vector(in->facing, &in_facing_vec);
	facing_to_vector(out->facing, &out_facing_vec);
	in_dir.x = -in_facing_vec.x;
	in_dir.y = -in_facing_vec.y;
	angle = compute_rotation_angle(&in_dir, &out_facing_vec);
	rotate_dvector(&ray->dir, angle);
	rotate_vector(&relative_pos, angle);
	ray->pos.x = out->world_x + relative_pos.x;
	ray->pos.y = out->world_y + relative_pos.y;
	ray->origin.x = ray->pos.x;
	ray->origin.y = ray->pos.y;
	update_ray(ray, out->virtual_cam);
}
