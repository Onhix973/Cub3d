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

void	draw_wall_slice(int x, t_draw draw_data, t_data *game)
{
	int	y;

	y = draw_data.drawstart;
	while (y <= draw_data.drawend)
	{
		img_pixel_put(x, y, WALL_COLOR, game);
		y++;
	}
}

#include <stdio.h>

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
		draw_wall_slice(x, draw_data, game);
		x++;
	}
	if (!game->img_ptr || !game->mlx_ptr || !game->win_ptr || !game->img_data)
	{
		printf("SUUUUUUUUU");
		exit(EXIT_FAILURE);
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img_ptr, 0, 0);
	return (0);
}
