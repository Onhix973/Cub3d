#include "structs.h"
#include "raycast.h"
#include <math.h>

t_vector	get_portal_center(t_portal *portal)
{
	t_vector	center;

	center.x = (portal->segment_start.x + portal->segment_end.x) / 2.0;
	center.y = (portal->segment_start.y + portal->segment_end.y) / 2.0;
	return (center);
}

float	get_portal_normal_angle(t_portal *portal)
{
	t_vector	dir;

	dir.x = portal->segment_end.x - portal->segment_start.x;
	dir.y = portal->segment_end.y - portal->segment_start.y;
	return (atan2(dir.y, dir.x) + M_PI / 2.0);
}

t_vector	get_portal_normal_vector(t_portal *portal)
{
	float		angle;
	t_vector	normal;

	angle = get_portal_normal_angle(portal);
	normal.x = cos(angle);
	normal.y = sin(angle);
	return (normal);
}

void	setup_portal_camera(t_portal *in, t_portal *out, t_player *player)
{
	t_vector	in_center;
	t_vector	out_center;
	float		rotation_angle;
	t_vector	relative_pos;
	t_vector	in_normal;
	t_vector	out_normal;

	in_center = get_portal_center(in);
	out_center = get_portal_center(out);
	in_normal = get_portal_normal_vector(in);
	out_normal = get_portal_normal_vector(out);
	relative_pos.x = player->pos.x - in_center.x;
	relative_pos.y = player->pos.y - in_center.y;
	rotation_angle = compute_rotation_angle(&in_normal, &out_normal) + M_PI;
	rotate_vector(&relative_pos, rotation_angle);
	out->virtual_cam.pos.x = out_center.x + relative_pos.x;
	out->virtual_cam.pos.y = out_center.y + relative_pos.y;
	out->virtual_cam.dir = player->dir;
	rotate_vector(&out->virtual_cam.dir, rotation_angle);
	out->virtual_cam.camera_plane = player->camera_plane;
	rotate_vector(&out->virtual_cam.camera_plane, rotation_angle);
}

void	teleport_ray(t_portal *in, t_portal *out, t_ray *ray, t_hit *hit_data)
{
	t_vector	in_center;
	t_vector	out_center;
	t_vector	hit_point;
	t_vector	relative_pos;
	t_vector	new_pos;
	t_vector	ray_dir;
	t_vector	in_normal;
	t_vector	out_normal;
	float		rotation_angle;

	in_center = get_portal_center(in);
	out_center = get_portal_center(out);
	in_normal = get_portal_normal_vector(in);
	out_normal = get_portal_normal_vector(out);
	if (hit_data->wall_tile_hit_side == HORIZONTAL_HIT)
	{
		if (ray->dir_x > 0)
			hit_point.x = ray->map_tile.x + 1.0f;
		else
			hit_point.x = ray->map_tile.x;
		hit_point.y = ray->pos_y + (hit_point.x - ray->pos_x) * (ray->dir_y / ray->dir_x);
	}
	else
	{
		if (ray->dir_y > 0)
			hit_point.y = ray->map_tile.y + 1.0f;
		else
			hit_point.y = ray->map_tile.y;
		hit_point.x = ray->pos_x + (hit_point.y - ray->pos_y) * (ray->dir_x / ray->dir_y);
	}
	relative_pos.x = hit_point.x - in_center.x;
	relative_pos.y = hit_point.y - in_center.y;
	rotation_angle = compute_rotation_angle(&in_normal, &out_normal) + M_PI;
	rotate_vector(&relative_pos, rotation_angle);
	new_pos.x = out_center.x + relative_pos.x;
	new_pos.y = out_center.y + relative_pos.y;
	ray->pos_x = new_pos.x;
	ray->pos_y = new_pos.y;
	ray->map_tile.x = (int)ray->pos_x;
	ray->map_tile.y = (int)ray->pos_y;
	ray_dir.x = ray->dir_x;
	ray_dir.y = ray->dir_y;
	rotate_vector(&ray_dir, rotation_angle);
	ray->dir_x = ray_dir.x;
	ray->dir_y = ray_dir.y;
	ray->dir_x = out->virtual_cam.dir.x + out->virtual_cam.camera_plane.x * ray->win_x_pos;
	ray->dir_y = out->virtual_cam.dir.y + out->virtual_cam.camera_plane.y * ray->win_x_pos;
	ray->delta_dist_x = fabs(1.0 / ray->dir_x);
	ray->delta_dist_y = fabs(1.0 / ray->dir_y);
	ray->cos_view_angle = ray->dir_x * out->virtual_cam.dir.x + ray->dir_y * out->virtual_cam.dir.y;
	init_ray_step_and_dist(&out->virtual_cam, ray);
}