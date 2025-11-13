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
		return ((ray->dist_next_hgrid - ray->delta_dist.x) \
		* ray->cos_view_angle);
	else
		return ((ray->dist_next_vgrid - ray->delta_dist.y) \
		* ray->cos_view_angle);
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

t_ray	init_ray(t_player *player, int screen_x)
{
	t_ray	ray;

	ray.win_x_pos = 2.0 * screen_x / (double)WIN_WIDTH - 1.0;
	ray.dir.x = player->dir.x + player->camera_plane.x * ray.win_x_pos;
	ray.dir.y = player->dir.y + player->camera_plane.y * ray.win_x_pos;
	ray.map_tile.x = (int)player->pos.x;
	ray.map_tile.y = (int)player->pos.y;
	ray.delta_dist.x = fabs(1.0 / ray.dir.x);
	ray.delta_dist.y = fabs(1.0 / ray.dir.y);
	ray.cos_view_angle = ray.dir.x * player->dir.x + ray.dir.y \
	* player->dir.y;
	ray.teleported_a = false;
	ray.teleported_b = false;
	init_ray_step_and_dist(player, &ray);
	return (ray);
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

t_hit	recursive_cast_ray(char **map_grid, t_ray *ray, t_portal_pair *portals,
		t_player *player, int depth)
{
	t_hit	hit_data = {0};
	t_vector	hit_p;

	if (depth >= MAX_PORTAL_RECURSION)
		return (cast_ray(map_grid, ray, player));
	ray->pos.x = player->pos.x;
	ray->pos.y = player->pos.y;
	while (map_grid[ray->map_tile.y][ray->map_tile.x] != '1')
	{
		if (ray->dist_next_hgrid < ray->dist_next_vgrid)
		{
			ray->dist_next_hgrid += ray->delta_dist.x;
			ray->map_tile.x += ray->tile_step.x;
			hit_data.wall_tile_hit_side = HORIZONTAL_HIT;
			hit_p.x = (float)ray->map_tile.x;
			hit_p.y = ray->pos.y + (hit_p.x - ray->pos.x) * (ray->dir.y / ray->dir.x);
			ray->pos.x = hit_p.x;
			ray->pos.y = hit_p.y;
		}
		else
		{
			ray->dist_next_vgrid += ray->delta_dist.y;
			ray->map_tile.y += ray->tile_step.y;
			hit_data.wall_tile_hit_side = VERTICAL_HIT;
			hit_p.y = (float)ray->map_tile.y;
			hit_p.x = ray->pos.x + (hit_p.y - ray->pos.y) * (ray->dir.x / ray->dir.y);
			ray->pos.x = hit_p.x;
			ray->pos.y = hit_p.y;
		}
		if (map_grid[ray->map_tile.y][ray->map_tile.x] == '1' && portals->linked)
		{
			if (!ray->teleported_a && check_for_portal(&portals->a, ray, &hit_data))
			{
				ray->teleported_a = true;
				teleport_ray(&portals->a, &portals->b, ray, &hit_data);
				return (recursive_cast_ray(map_grid, ray, portals, player, depth + 1));
			}
			if (!ray->teleported_b && check_for_portal(&portals->b, ray, &hit_data))
			{
				ray->teleported_b = true;
				teleport_ray(&portals->b, &portals->a, ray, &hit_data);
				return (recursive_cast_ray(map_grid, ray, portals, player, depth + 1));
			}
		}
	}
	hit_data.proj_wall_hit_dist = \
	compute_projected_wall_dist(ray, hit_data.wall_tile_hit_side);
	return (hit_data);	
}


t_hit	cast_ray(char **map_grid, t_ray *ray, t_player *player)
{
	t_hit	hit_data = {0};
	t_vector	hit_p;

	ray->pos.x = player->pos.x;
	ray->pos.y = player->pos.y;
	while (map_grid[ray->map_tile.y][ray->map_tile.x] != '1')
	{
		if (ray->dist_next_hgrid < ray->dist_next_vgrid)
		{
			ray->dist_next_hgrid += ray->delta_dist.x;
			ray->map_tile.x += ray->tile_step.x;
			hit_data.wall_tile_hit_side = HORIZONTAL_HIT;
			hit_p.x = (float)ray->map_tile.x;
			hit_p.y = ray->pos.y + (hit_p.x - ray->pos.x) * (ray->dir.y / ray->dir.x);
			ray->pos.x = hit_p.x;
			ray->pos.y = hit_p.y;
		}
		else
		{
			ray->dist_next_vgrid += ray->delta_dist.y;
			ray->map_tile.y += ray->tile_step.y;
			hit_data.wall_tile_hit_side = VERTICAL_HIT;
			hit_p.y = (float)ray->map_tile.y;
			hit_p.x = ray->pos.x + (hit_p.y - ray->pos.y) * (ray->dir.x / ray->dir.y);
			ray->pos.x = hit_p.x;
			ray->pos.y = hit_p.y;
		}
	}
	hit_data.proj_wall_hit_dist = \
	compute_projected_wall_dist(ray, hit_data.wall_tile_hit_side);
	return (hit_data);	
}

