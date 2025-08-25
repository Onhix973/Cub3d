#include "cub3D.h"
#include "raycast.h"
#include "math.h"

void	img_pixel_put(int x, int y, int color, t_data *game)
{
	char	*pixel;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	pixel = game->img_data + (y * game->size_line) + (x * (game->bpp / 8));
	*(unsigned int *)pixel = color;
}

void	init_ray_helper(t_player *player, t_ray *ray)
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
	init_ray_helper(player, &ray);
	return (ray);
}

t_hit	cast_ray_helper(t_hit hit_data, t_ray *ray)
{
	if (hit_data.side == 0)
		hit_data.perpwalldist = ray->sidedistx - ray->deltadistx;
	else
		hit_data.perpwalldist = ray->sidedisty - ray->deltadisty;
	return (hit_data);
}

t_hit	cast_ray(char **map, t_ray *ray)
{
	t_hit	hit_data;
	int		hit;
	int		side;

	hit = 0;
	side = 0;
	while (!hit)
	{
		if (ray->sidedistx < ray->sidedisty)
		{
			ray->sidedistx += ray->deltadistx;
			ray->mapx += ray->stepx;
			side = 0;
		}
		else
		{
			ray->sidedisty += ray->deltadisty;
			ray->mapy += ray->stepy;
			side = 1;
		}
		if (map[ray->mapy][ray->mapx] == '1')
			hit = 1;
	}
	hit_data.side = side;
	return (cast_ray_helper(hit_data, ray));
}
