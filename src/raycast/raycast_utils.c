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
	ray.proj_wall_hit_dist = 0.0;
	init_ray_step_and_dist(player, &ray);
	return (ray);
}

void	cast_ray(char **map_grid, t_ray *ray)
{
	while (map_grid[ray->map_tile.y][ray->map_tile.x] != '1')
	{
		if (ray->dist_next_hgrid < ray->dist_next_vgrid)
		{
			ray->dist_next_hgrid += ray->delta_dist.x;
			ray->map_tile.x += ray->tile_step.x;
			ray->wall_tile_hit_side = HORIZONTAL_HIT;
		}
		else
		{
			ray->dist_next_vgrid += ray->delta_dist.y;
			ray->map_tile.y += ray->tile_step.y;
			ray->wall_tile_hit_side = VERTICAL_HIT;
		}
	}
	ray->proj_wall_hit_dist = \
	compute_projected_wall_dist(ray, ray->wall_tile_hit_side);
}
