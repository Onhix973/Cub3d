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

void	find_dist_to_nearest_tile(t_player *player, t_ray *ray)
{
	if (ray->dirx < 0)
	{
		ray->stepx = -1;
		ray->sidedistx = (player->pos.x - ray->mapx) * ray->deltadistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedistx = (ray->mapx + 1.0 - player->pos.x) * ray->deltadistx;
	}
	if (ray->diry < 0)
	{
		ray->stepy = -1;
		ray->sidedisty = (player->pos.y - ray->mapy) * ray->deltadisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedisty = (ray->mapy + 1.0 - player->pos.y) * ray->deltadisty;
	}
}

t_ray	init_ray(t_player *player, int x)
{
	t_ray	ray;

	ray.camerax = 2 * x / (double)WIN_WIDTH - 1;
	ray.dirx = player->dir.x + player->plane.x * ray.camerax;
	ray.diry = player->dir.y + player->plane.y * ray.camerax;
	ray.mapx = (int)player->pos.x;
	ray.mapy = (int)player->pos.y;
	ray.deltadistx = fabs(1 / ray.dirx);
	ray.deltadisty = fabs(1 / ray.diry);
	ray.cos_angle = ray.dirx * player->dir.x + ray.diry * player->dir.y;
	find_dist_to_nearest_tile(player, &ray);
	return (ray);
}

t_hit	cast_ray(char **map, t_ray *ray)
{
	t_hit	hit_data = {0};
	double	raw_dist;

	while (map[ray->mapy][ray->mapx] != '1')
	{
		if (ray->sidedistx < ray->sidedisty)
		{
			ray->sidedistx += ray->deltadistx;
			ray->mapx += ray->stepx;
			hit_data.side = 0;
		}
		else
		{
			ray->sidedisty += ray->deltadisty;
			ray->mapy += ray->stepy;
			hit_data.side = 1;
		}
	}
	if (hit_data.side == 0)
		raw_dist = ray->sidedistx - ray->deltadistx;
	else
		raw_dist = ray->sidedisty - ray->deltadisty;
	hit_data.perpwalldist = raw_dist * ray->cos_angle;
	return (hit_data);
}
