#include "raycast.h"
#include "cub3D.h"
#include "libft.h"
#include "mlx.h"
#include <math.h>
#include <stdio.h>

//TODO
#include <string.h>

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
	int	cx;
	int	cy;
	int	i;

	cx = WIN_WIDTH >> 1;
	cy = WIN_HEIGHT >> 1;
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
	if (game->key_state->c && !game->g_states.mouse_activated)
	{
		XFixesHideCursor(game->display, game->main_win);
		XFlush(game->display);
		game->g_states.mouse_activated = true;
	}
	else if (game->key_state->v && game->g_states.mouse_activated)
	{
		XFixesShowCursor(game->display, game->main_win);
		XFlush(game->display);
		game->g_states.mouse_activated = false;
	}
}

#include <stdio.h>
void	fps_counter(float delta_time, t_data *game)
{
	static float elapsed_time = 0.0f;
	static int frame_count = 0;
	static int fps = 0;
	char		*fps_str;
	static char	*fps_display;

	elapsed_time += delta_time;
	frame_count++;

	if (elapsed_time >= 1.0f)
	{
		fps = frame_count / elapsed_time;
		fps_str = ft_itoa(fps);
		// free(fps_display);
		fps_display = ft_strjoin("FPS : ", fps_str);
		free(fps_str);
		elapsed_time = 0.0f;
		frame_count = 0;
	}
	if (fps_display)
		mlx_string_put(game->mlx, game->win, WIN_WIDTH - 80, 50, 0xFFFFFF, \
			fps_display);
}

void	select_map(t_data *game)
{
	if (game->g_states.fs_map)
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
}

void	portal_painter(t_data *game, t_ray *ray, t_hit * hit_data, int x)
{
	bool	is_portal_slice = false;

	is_portal_slice = check_for_portal(&game->portals.a, ray, hit_data) \
	|| check_for_portal(&game->portals.b, ray, hit_data);
	draw_wall_slice(x, game, ray, hit_data);
	if (is_portal_slice)
		draw_portal_slice(x, game, ray, hit_data);
}

void	portal_builder(t_data *game, t_ray *ray, t_hit *hit_data, int x)
{
	if (game->g_states.attack_triggered)
	{
		if (x == WIN_WIDTH >> 1)
		{
			if ((hit_data->wall_tile_hit_side == VERTICAL_HIT \
				|| hit_data->wall_tile_hit_side == HORIZONTAL_HIT) 
				&& hit_data->proj_wall_hit_dist < MAX_PORTAL_RANGE)
			{
				if (!game->portals.a.active)
				{
					create_portal(ray, hit_data, &game->portals.a);
					define_portal_segment(&game->portals.a);
					game->portals.a.active = true;
				}
				else if (!game->portals.b.active)
				{
					create_portal(ray, hit_data, &game->portals.b);
					define_portal_segment(&game->portals.b);
					game->portals.b.active = true;
					game->portals.linked = true;
				}
			}
			game->g_states.attack_triggered = false;
		}
	}
}

#include <sys/time.h>

int	game_loop(void *param)
{
	t_data		*game;
	int			x;
	t_ray		ray;
	t_hit		hit_data;
	float		delta_time;

	x = 0;
	game = (t_data *)param;
	delta_time = get_delta_time();
	game_states_mswitch(game);
	update_player(game, delta_time);
	teleport_player_crossing_portal(game);
	// ft_memcpy(game->main_img.data, game->background.data, WIN_HEIGHT * game->background.size_line);
	//TODO REMOVE MEMCPY FOR MANDATORY
	if (game->portals.linked && game->portals.a.active && game->portals.b.active)
	{
		printf("setting up portal virtual camera");
		setup_portal_camera(&game->portals.a, &game->portals.b, game->player);
		setup_portal_camera(&game->portals.b, &game->portals.a, game->player);
	}
	memcpy(game->main_img.data, game->background.data, WIN_HEIGHT * game->background.size_line);
	handle_cursor(game);
	while (x < WIN_WIDTH)
	{
		ray = init_ray(game->player, x);
		hit_data = recursive_cast_ray(game->map, &ray, &game->portals, 0);
		portal_builder(game, &ray, &hit_data, x);
		portal_painter(game, &ray, &hit_data, x);
		x++;
	}
	draw_crosshair(game);
	select_animation(game, delta_time);
	select_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->main_img.ptr, 0, 0);
	fps_counter(delta_time, game);
	return (0);
}
