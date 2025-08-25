#include "raycast.h"
#include "cub3D.h"
#include "libft.h"
#include "mlx.h"
#include <math.h>

t_draw	compute_draw_limits(double perpwalldist)
{
	t_draw	draw_data;

	draw_data.lineheight = (int)(WIN_HEIGHT / perpwalldist);
	draw_data.drawstart = -draw_data.lineheight / 2 + WIN_HEIGHT / 2;
	if (draw_data.drawstart < 0)
		draw_data.drawstart = 0;
	draw_data.drawend = draw_data.lineheight / 2 + WIN_HEIGHT / 2;
	if (draw_data.drawend >= WIN_HEIGHT)
		draw_data.drawend = WIN_HEIGHT - 1;
	return (draw_data);
}

void	draw_wall_slice(int x, t_draw draw_data, t_data *game, t_ray ray, t_hit hit_data)
{
	int	y;
	int	line_height;
	double wall_x;

	y = draw_data.drawstart;
	line_height = draw_data.lineheight;
	if (hit_data.side == 0)
		wall_x = game->player->pos.y + hit_data.perpwalldist * ray.diry;
	else
		wall_x = game->player->pos.x + hit_data.perpwalldist * ray.dirx;
	wall_x -= floor(wall_x);

	int	tex_x = (int)(wall_x * (double)game->wall.width);
	if ((hit_data.side == 0 && ray.dirx > 0) || (hit_data.side == 1 && ray.diry < 0))
		tex_x = game->wall.width - tex_x - 1;
	while (y <= draw_data.drawend)
	{
		int d = (y - WIN_HEIGHT / 2 + line_height / 2) * 256;
		int tex_y = ((d * game->wall.height) / line_height) / 256;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= game->wall.height)
			tex_y = game->wall.height - 1;
		if (tex_x < 0)
			tex_x = 0;
		if (tex_x >= game->wall.width)
			tex_x = game->wall.width - 1;
		char *pixel = game->wall.data + tex_y * game->wall.size_line +
		tex_x * (game->wall.bpp / 8);
		int color = *(int *)pixel;

		img_pixel_put(x, y, color, game);
		y++;
	}
}

int	raycast_loop(void *param)
{
	t_data		*game;
	int			x;
	t_ray		ray;
	t_hit		hit_data;
	t_draw		draw_data;
	float		delta_time;

	game = (t_data *)param;
	x = 0;
	delta_time = get_delta_time();
	update_player(game, delta_time, game->key_state);
	ft_memset(game->img_data, 0, WIN_HEIGHT * game->size_line);
	while (x < WIN_WIDTH)
	{
		ray = init_ray(game->player, x);
		hit_data = cast_ray(game->map, &ray);
		draw_data = compute_draw_limits(hit_data.perpwalldist);
		draw_wall_slice(x, draw_data, game, ray, hit_data);
		x++;
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img_ptr, 0, 0);
	return (0);
}
