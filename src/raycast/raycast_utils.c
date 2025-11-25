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
		return ((ray->dist_next_hgrid - ray->delta_dist.x));
	else
		return ((ray->dist_next_vgrid - ray->delta_dist.y));
}

void	init_ray_step_and_dist(t_player *player, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->tile_step.x = -1;
		ray->dist_next_hgrid = (player->pos.x - ray->map_tile.x) \
		* ray->delta_dist.x;
	}
	else
	{
		ray->tile_step.x = 1;
		ray->dist_next_hgrid = (ray->map_tile.x + 1.0 - player->pos.x) \
		* ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->tile_step.y = -1;
		ray->dist_next_vgrid = (player->pos.y - ray->map_tile.y) \
		* ray->delta_dist.y;
	}
	else
	{
		ray->tile_step.y = 1;
		ray->dist_next_vgrid = (ray->map_tile.y + 1.0 - player->pos.y) \
		* ray->delta_dist.y;
	}
}

float	dvector_length(t_double_vector v)
{
	return (sqrtf(v.x * v.x + v.y * v.y));
}

t_double_vector	normalize_dvector(t_double_vector v)
{
	t_double_vector	new;
	const float	v_length = dvector_length(v);

	if (v_length == 0)
	{
		new.x = 0;
		new.y = 0;
	}
	else
	{
		new.x = v.x / v_length;
		new.y = v.y / v_length;
	}
	return (new);
}

t_ray	init_ray(t_player *player, int screen_x)
{
	t_ray	ray;

	ray.win_x_pos = 2.0 * screen_x / (double)WIN_WIDTH - 1.0;
	ray.dir.x = player->dir.x + player->camera_plane.x * ray.win_x_pos;
	ray.dir.y = player->dir.y + player->camera_plane.y * ray.win_x_pos;
	ray.dir = normalize_dvector(ray.dir);
	ray.origin.x = player->pos.x;
	ray.origin.y = player->pos.y;
	ray.pos.x = ray.origin.x; 
	ray.pos.y = ray.origin.y;
	ray.map_tile.x = (int)player->pos.x;
	ray.map_tile.y = (int)player->pos.y;
	ray.delta_dist.x = fabs(1.0 / ray.dir.x);
	ray.delta_dist.y = fabs(1.0 / ray.dir.y);
	ray.cos_view_angle = ray.dir.x * player->dir.x + ray.dir.y \
	* player->dir.y;
	ray.proj_wall_hit_dist = 0.0;
	ray.collision_dist = 0.0;
	init_ray_step_and_dist(player, &ray);
	return (ray);
}

#include <stdio.h>
#include <unistd.h>

bool	is_portal_side(t_portal *portal, t_ray *ray)
{
	t_vector	ray_portal;

	ray_portal.x = ray->map_tile.x;
	ray_portal.y = ray->map_tile.y;
	if (!ray->wall_tile_hit_side)
	{
		if (ray->dir.x < 0)
			ray_portal.x += 1.0f;
	}
	else
	{
		if (ray->dir.y < 0)
			ray_portal.y += 1.0f;
	}
	return (portal->active && is_point_on_segment(ray_portal, portal->segment_start, 
		portal->segment_end));
}

double	compute_euclidian_distance(t_vector hit_point, t_vector cam_pos)
{
	double	x_squared;
	double	y_squared;

	x_squared = (hit_point.x - cam_pos.x) * (hit_point.x - cam_pos.x);
	y_squared = (hit_point.y - cam_pos.y) * (hit_point.y - cam_pos.y);
	return (sqrt(x_squared + y_squared));
}

void	cast_ray(char **map_grid, t_ray *ray)
{
	t_vector	hit_p;
 
	while (map_grid[ray->map_tile.y][ray->map_tile.x] != '1')
	{
		if (ray->dist_next_hgrid < ray->dist_next_vgrid)
		{
			ray->dist_next_hgrid += ray->delta_dist.x;
			ray->map_tile.x += ray->tile_step.x;
			ray->wall_tile_hit_side = HORIZONTAL_HIT;
			hit_p.x = (float)ray->map_tile.x;
			hit_p.y = ray->pos.y + (hit_p.x - ray->pos.x) 
			* (ray->dir.y / ray->dir.x);
			ray->pos.x = hit_p.x;
			ray->pos.y = hit_p.y;
			ray->collision_dist = sqrtf(
        	(hit_p.x - ray->origin.x)*(hit_p.x - ray->origin.x) +
        	(hit_p.y - ray->origin.y)*(hit_p.y - ray->origin.y));
		}
		else
		{
			ray->dist_next_vgrid += ray->delta_dist.y;
			ray->map_tile.y += ray->tile_step.y;
			ray->wall_tile_hit_side = VERTICAL_HIT;
			hit_p.y = (float)ray->map_tile.y;
			hit_p.x = ray->pos.x + (hit_p.y - ray->pos.y) 
			* (ray->dir.x / ray->dir.y);
			ray->pos.x = hit_p.x;
			ray->pos.y = hit_p.y;
			ray->collision_dist = sqrtf(
        	(hit_p.x - ray->origin.x)*(hit_p.x - ray->origin.x) +
        	(hit_p.y - ray->origin.y)*(hit_p.y - ray->origin.y));
		}
	}
	ray->proj_wall_hit_dist = \
	compute_projected_wall_dist(ray, ray->wall_tile_hit_side);
}
