#include "raycast.h"
#include "cub3D.h"
#include "libft.h"
#include "mlx.h"
#include <math.h>

//TODO
#include <string.h>
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

//TODO
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

void	portal_painter(t_data *game, t_ray *ray, int x)
{
	draw_wall_slice(x, game, ray);
	if ((check_for_portal(&game->portals.a, ray) && game->portals.a.active) 
	|| (check_for_portal(&game->portals.b, ray) && game->portals.b.active))
		draw_portal_slice(x, game, ray);
}

void	portal_builder(t_data *game, t_ray *ray, int x)
{
	if (game->g_states.attack_triggered)
	{
		if (x == WIN_WIDTH >> 1)
		{
			if ((ray->wall_tile_hit_side == VERTICAL_HIT \
				|| ray->wall_tile_hit_side == HORIZONTAL_HIT) 
				&& ray->proj_wall_hit_dist < MAX_PORTAL_RANGE)
			{
				if (!game->portals.a.active)
				{
					create_portal(ray, &game->portals.a);
					define_portal_segment(&game->portals.a);
					game->portals.a.active = true;
				}
				else if (!game->portals.b.active)
				{
					create_portal(ray, &game->portals.b);
					define_portal_segment(&game->portals.b);
					game->portals.b.active = true;
					game->portals.linked = true;
				}
			}
			game->g_states.attack_triggered = false;
		}
	}
}

void	game_loop_display_wrapper(t_data *game, float delta_time)
{
	draw_crosshair(game);
	select_animation(game, delta_time);
	select_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->main_img.ptr, 0, 0);
}

int	game_loop(void *param)
{
	t_data		*game;
	int			x;
	t_ray		ray;
	float		delta_time;

	x = 0;
	game = (t_data *)param;
	delta_time = get_delta_time();
	game_states_mswitch(game);
	update_player(game, delta_time);
	teleport_player_crossing_portal(game);
	// ft_memcpy(game->main_img.data, game->background.data, WIN_HEIGHT * game->background.size_line);
	//TODO REMOVE MEMCPY FOR MANDATORY
	memcpy(game->main_img.data, game->background.data, 
		WIN_HEIGHT * game->background.size_line);
	handle_cursor(game);
	while (x < WIN_WIDTH)
	{
		ray = init_ray(game->player, x);
		cast_ray(game->map, &ray);
		portal_builder(game, &ray, x);
		portal_painter(game, &ray, x);
		x++;
	}
	game_loop_display_wrapper(game, delta_time);
	fps_counter(delta_time, game);
	return (0);
}
