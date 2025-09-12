#include "raycast.h"
#include "cub3D.h"
#include "libft.h"
#include "mlx.h"
#include <math.h>

void	draw_ceiling_and_floor(t_img *img, int ceiling_color, int floor_color)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIN_WIDTH)
	{
		y = 0;
		while (y < WIN_HEIGHT)
		{
			img_pixel_put(x, y, ceiling_color, img);
			y++;
		}
		y = WIN_HEIGHT >> 1;
		while (y < WIN_HEIGHT)
		{
			img_pixel_put(x, y, floor_color, img);
			y++;
		}
		x++;
	}
}

void	draw_crosshair(t_data *game)
{
	int	cx = WIN_WIDTH >> 1;
	int	cy = WIN_HEIGHT >> 1;
	int	i;

	i = -CROSSHAIR_SIZE;
	while (i <= CROSSHAIR_SIZE)
	{
		img_pixel_put(cx + i, cy, CROSSHAIR_COLOR, &game->main_img);
		img_pixel_put(cx, cy + i, CROSSHAIR_COLOR, &game->main_img);
		i++;
	}
}

#include <X11/X.h>
#include <X11/extensions/Xfixes.h>

void	handle_cursor(t_data *game)
{
	static	bool hidden;

	if (game->key_state->c && hidden == false)
	{
		XFixesHideCursor(game->display, game->main_win);
		XFlush(game->display);
		hidden = true;
		game->mouse_activated = true;
	}
	else if (game->key_state->v && hidden == true)
	{
		XFixesShowCursor(game->display, game->main_win);
		XFlush(game->display);
		hidden = false;
		game->mouse_activated = false;
	}
}

#include <stdio.h>
void	fps_counter(float delta_time, t_data *game)
{
	static float elapsed_time = 0.0f;
	static int frame_count = 0;
	static int fps = 0;
	char		*fps_str;
	static char	*fps_display = NULL;

	elapsed_time += delta_time;
	frame_count++;

	if (elapsed_time >= 1.0f)
	{
		fps = frame_count / elapsed_time;
		fps_str = ft_itoa(fps);
		free(fps_display);
		fps_display = ft_strjoin("FPS : ", fps_str);
		free(fps_str);
		elapsed_time = 0.0f;
		frame_count = 0;
	}
	if (fps_display)
		mlx_string_put(game->mlx, game->win, WIN_WIDTH - 80, 50, 0xFFFFFF, fps_display);
}

int	raycast_loop(void *param)
{
	t_data		*game;
	int			x;
	t_ray		ray;
	t_hit		hit_data;
	float		delta_time;

	x = 0;
	game = (t_data *)param;
	delta_time = get_delta_time();
	if (game->key_state->tab && !game->fs_map)
	{
		game->key_state->tab = false;
		game->fs_map = true;
	}
	else if (game->key_state->tab && game->fs_map)
	{
		game->key_state->tab = false;
		game->fs_map = false;
	}
	update_player(game, delta_time);
	ft_memcpy(game->main_img.data, game->background.data, WIN_HEIGHT * game->background.size_line);
	handle_cursor(game);
	while (x < WIN_WIDTH)
	{
		ray = init_ray(game->player, x);
		hit_data = cast_ray(game->map, &ray);
		draw_wall_slice(x, game, &ray, &hit_data);
		x++;
	}
	if (game->fs_map)
	{
		update_fs_minimap_camera_offset(game);
		draw_fs_minimap(game);
		draw_fs_minimap_player(game);
	}
	else
	{
		update_minimap_camera_offset(game);
		draw_entire_minimap(game);
		draw_minimap_player(game);
	}
	draw_crosshair(game);
	mlx_put_image_to_window(game->mlx, game->win, game->main_img.ptr, 0, 0);
	fps_counter(delta_time, game);
	return (0);
}
