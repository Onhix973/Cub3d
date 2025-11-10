#include "cub3D.h"
#include "raycast.h"
#include "math.h"

void	img_pixel_put(int x, int y, int color, t_img *img)
{
	char	*pixel;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	pixel = img->data + (y * img->size_line) + (x * (img->bpp / 8));
	*(unsigned int *)pixel = color;
}

double	compute_projected_wall_dist(t_ray *ray, bool wall_tile_hit_side)
{
	if (wall_tile_hit_side == HORIZONTAL_HIT)
		return ((ray->dist_next_hgrid - ray->delta_dist_x) \
		* ray->cos_view_angle);
	else
		return ((ray->dist_next_vgrid - ray->delta_dist_y) \
		* ray->cos_view_angle);
}

void	init_ray_step_and_dist(t_player *player, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->tile_step.x = -1;
		ray->dist_next_hgrid = (player->pos.x - ray->map_tile.x) \
		* ray->delta_dist_x;
	}
	else
	{
		ray->tile_step.x = 1;
		ray->dist_next_hgrid = (ray->map_tile.x + 1.0 - player->pos.x) \
		* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->tile_step.y = -1;
		ray->dist_next_vgrid = (player->pos.y - ray->map_tile.y) \
		* ray->delta_dist_y;
	}
	else
	{
		ray->tile_step.y = 1;
		ray->dist_next_vgrid = (ray->map_tile.y + 1.0 - player->pos.y) \
		* ray->delta_dist_y;
	}
}

t_ray	init_ray(t_player *player, int screen_x)
{
	t_ray	ray;

	ray.win_x_pos = 2.0 * screen_x / (double)WIN_WIDTH - 1.0;
	ray.dir_x = player->dir.x + player->camera_plane.x * ray.win_x_pos;
	ray.dir_y = player->dir.y + player->camera_plane.y * ray.win_x_pos;
	ray.map_tile.x = (int)player->pos.x;
	ray.map_tile.y = (int)player->pos.y;
	ray.delta_dist_x = fabs(1.0 / ray.dir_x);
	ray.delta_dist_y = fabs(1.0 / ray.dir_y);
	ray.cos_view_angle = ray.dir_x * player->dir.x + ray.dir_y \
	* player->dir.y;
	init_ray_step_and_dist(player, &ray);
	return (ray);
}

void	init_ray_from_camera(t_player *virtual_cam, double win_x_pos, t_ray *ray)
{
	ray->win_x_pos = win_x_pos;
	ray->dir_x = virtual_cam->dir.x + virtual_cam->camera_plane.x * ray->win_x_pos;
	ray->dir_y = virtual_cam->dir.y + virtual_cam->camera_plane.y * ray->win_x_pos;
	ray->map_tile.x = (int)ray->map_tile.x;
	ray->map_tile.y = (int)ray->map_tile.y;
	ray->delta_dist_x = fabs(1.0 / ray->dir_x);
	ray->delta_dist_y = fabs(1.0 / ray->dir_y);
	ray->cos_view_angle = ray->dir_x * virtual_cam->dir.x + ray->dir_y \
	* virtual_cam->dir.y;
	init_ray_step_and_dist(virtual_cam, ray);
}

#include <stdio.h>
#include <unistd.h>

bool	is_portal_side(t_portal *portal, t_ray *ray, t_hit *hit_data)
{
	t_vector	ray_portal;

	(void)hit_data;
	ray_portal.x = ray->map_tile.x;
	ray_portal.y = ray->map_tile.y;
	if (!hit_data->wall_tile_hit_side)
	{
		if (ray->dir_x < 0)
			ray_portal.x += 1.0f;
	}
	else
	{
		if (ray->dir_y < 0)
			ray_portal.y += 1.0f;
	}
	return (portal->active && is_point_on_segment(ray_portal, portal->segment_start, 
		portal->segment_end));
}

//TODO

void	setup_portal_camera(t_portal *in, t_portal *out, t_player *player)
{
	t_vector	in_facing_vec;
	t_vector	out_facing_vec;
	t_vector	relative_pos;
	float		angle;

	facing_to_vector(in->facing, &in_facing_vec);
	facing_to_vector(out->facing, &out_facing_vec);
	relative_pos.x = player->pos.x - in->world_x;
	relative_pos.y = player->pos.y - out->world_y;
	angle = compute_rotation_angle(&in_facing_vec, &out_facing_vec) + M_PI;
	rotate_vector(&relative_pos, angle);
	out->virtual_cam.dir = player->dir;
	rotate_vector(&out->virtual_cam.dir, angle);
	out->virtual_cam.camera_plane = player->camera_plane;
	rotate_vector(&out->virtual_cam.camera_plane, angle);
	out->virtual_cam.pos.x = out->world_x + relative_pos.x;
	out->virtual_cam.pos.y = out->world_y + relative_pos.y;
}

void	teleport_ray(t_portal *in, t_portal *out, t_ray *ray)
{
	t_vector	in_facing_vec;
	t_vector	out_facing_vec;
	t_vector	relative_pos;
	float		angle;
	t_vector	ray_dir;

	ray_dir.x = ray->dir_x;
	ray_dir.y = ray->dir_y;
	facing_to_vector(in->facing, &in_facing_vec);
	facing_to_vector(out->facing, &out_facing_vec);
	relative_pos.x = ray->map_tile.x - in->world_x ;
	relative_pos.y = ray->map_tile.y - in->world_y;
	angle = compute_rotation_angle(&in_facing_vec, &out_facing_vec) + M_PI;
	rotate_vector(&relative_pos, angle);
	rotate_vector(&ray_dir, angle);
	ray->map_tile.x = out->world_x;
	ray->map_tile.y = out->world_y;
	ray->dir_x = ray_dir.x;
	ray->dir_y = ray_dir.y;
}

t_hit	recursive_cast_ray(char **map_grid, t_ray *ray, t_portal_pair *portals, 
		int max_depth)
{
	t_hit	hit_data = {0};

	if (max_depth > MAX_PORTAL_RECURSION)
		return (cast_ray(map_grid, ray));
	while (map_grid[ray->map_tile.y][ray->map_tile.x] != '1')
	{
		if (ray->dist_next_hgrid < ray->dist_next_vgrid)
		{
			ray->dist_next_hgrid += ray->delta_dist_x;
			ray->map_tile.x += ray->tile_step.x;
			hit_data.wall_tile_hit_side = HORIZONTAL_HIT;
		}
		else
		{
			ray->dist_next_vgrid += ray->delta_dist_y;
			ray->map_tile.y += ray->tile_step.y;
			hit_data.wall_tile_hit_side = VERTICAL_HIT;
		}
		if (map_grid[ray->map_tile.y][ray->map_tile.x] == '1'  
			&& portals->linked && check_for_portal(&portals->a, ray, &hit_data))
		{
			printf("teleporting ray\n");
			teleport_ray(&portals->a, &portals->b, ray);
			init_ray_from_camera(&portals->a.virtual_cam, ray->win_x_pos, ray);
			return (recursive_cast_ray(map_grid, ray, portals, max_depth + 1));
		}
		if (map_grid[ray->map_tile.y][ray->map_tile.x] == '1' 
			&& portals->linked && check_for_portal(&portals->b, ray, &hit_data))
		{
			printf("teleporting ray\n");
			teleport_ray(&portals->b, &portals->a, ray);
			init_ray_from_camera(&portals->b.virtual_cam, ray->win_x_pos, ray);
			return (recursive_cast_ray(map_grid, ray, portals, max_depth + 1));
		}
	}
	hit_data.proj_wall_hit_dist = 
	(compute_projected_wall_dist(ray, hit_data.wall_tile_hit_side));
	return (hit_data);
}

t_hit	cast_ray(char **map_grid, t_ray *ray)
{
	t_hit	hit_data = {0};

	while (map_grid[ray->map_tile.y][ray->map_tile.x] != '1')
	{
		if (ray->dist_next_hgrid < ray->dist_next_vgrid)
		{
			ray->dist_next_hgrid += ray->delta_dist_x;
			ray->map_tile.x += ray->tile_step.x;
			hit_data.wall_tile_hit_side = HORIZONTAL_HIT;
		}
		else
		{
			ray->dist_next_vgrid += ray->delta_dist_y;
			ray->map_tile.y += ray->tile_step.y;
			hit_data.wall_tile_hit_side = VERTICAL_HIT;
		}
	}
	hit_data.proj_wall_hit_dist = \
	compute_projected_wall_dist(ray, hit_data.wall_tile_hit_side);
	return (hit_data);	
}

