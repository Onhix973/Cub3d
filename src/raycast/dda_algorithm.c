#include "raycast.h"
#include "cub3D.h"
#include "libft.h"
#include "mlx.h"
#include <math.h>

void img_pixel_put(int x, int y, int color, t_data *game)
{
	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	char *pixel;
	pixel = game->img_data + (y * game->size_line) + (x * (game->bpp / 8));
	*(unsigned int *)pixel = color;
}

int raycast_loop(void * param)
{
	t_data *game = (t_data *)param;
	t_player *player = game->player;
	char **map = game->map;
	ft_memset(game->img_data, 0, WIN_HEIGHT * game->size_line);
	for (int x = 0; x < WIN_WIDTH; x++)
	{
		double camerax = 2 * x / (double)WIN_WIDTH - 1;
		double raydirx = player->dir.x + player->plane.x * camerax;
		double raydiry = player->dir.y + player->plane.y * camerax;

		int mapx = (int)player->pos.x;
		int mapy = (int)player->pos.y;

		double sidedistx;
		double sidedisty;

		double deltadistx = fabs(1 / raydirx);
		double deltadisty = fabs(1 / raydiry);

		int stepx, stepy;

		if (raydirx < 0)
		{
			stepx = -1;
			sidedistx = (player->pos.x - mapx) * deltadistx;
		}
		else
		{
			stepx = 1;
			sidedistx = (mapx + 1.0 - player->pos.x) * deltadistx;
		}
		if (raydiry < 0)
		{
			stepy = -1;
			sidedisty = (player->pos.y - mapy) * deltadisty;
		}
		else
		{
			stepy = 1;
			sidedisty = (mapy + 1.0 - player->pos.y) * deltadisty;
		}
		int	hit = 0;
		int side;
		
		while (!hit)
		{
			if (sidedistx < sidedisty)
			{
				sidedistx += deltadistx;
				mapx += stepx;
				side = 0;
			}
			else
			{
				sidedisty += deltadisty;
				mapy += stepy;
				side = 1;
			}
			if (map[mapy][mapx] == '1')
				hit = 1;
		}
		double perpwalldist = (side == 0) ? (sidedistx - deltadistx) : (sidedisty - deltadisty);
		int lineheight = (int)(WIN_HEIGHT / perpwalldist);
		int drawstart = -lineheight / 2 + WIN_HEIGHT / 2;
		if (drawstart < 0)
			drawstart = 0;
		int drawend = lineheight / 2 + WIN_HEIGHT / 2;
		if (drawend >= WIN_HEIGHT)
			drawend = WIN_HEIGHT - 1;
		for (int y = drawstart; y < drawend; y++)
			img_pixel_put(x, y , WALL_COLOR, game);
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img_ptr, 0, 0);
	return (0);
}

t_ray	init_ray(t_player *player, int x)
{
	t_ray ray;

	ray.camerax = 2 * x / (double)WIN_WIDTH - 1;
	ray.dirx = player->dir.x + player->plane.x * ray.camerax;
	ray.diry = player->dir.y + player->plane.y * ray.camerax;
	ray.mapx = (int)player->pos.x;
	ray.mapy = (int)

}