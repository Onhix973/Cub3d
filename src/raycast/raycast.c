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

t_texture	get_wall_tex(t_hit *hit_data, t_ray *ray, t_data *game, \
	double *wall_x)
{
	if (!hit_data->side)
	{
		*wall_x = game->player->pos.y + hit_data->perpwalldist * ray->diry;
		if (ray->dirx > 0)
			return (game->e_wall);
		else
			return (game->w_wall);
	}
	else
	{
		*wall_x = game->player->pos.x + hit_data->perpwalldist * ray->dirx;
		if (ray->diry > 0)
			return (game->s_wall);
		else
			return (game->n_wall);
	}
}

void	draw_wall_slice(int x, t_draw draw_data, t_data *game, t_ray ray, t_hit hit_data)
{
	int			y;
	int			line_height;
	double		wall_x;
	t_texture	wall;

	y = draw_data.drawstart;
	line_height = draw_data.lineheight;
	wall = get_wall_tex(&hit_data, &ray, game, &wall_x);
	wall_x -= floor(wall_x);
	int	tex_x = (int)(wall_x * (double)wall.width);
	int	d;
	int	tex_y;
	char *pixel;
	int color;
	if ((hit_data.side == 0 && ray.dirx > 0) || (hit_data.side == 1 && ray.diry < 0))
		tex_x = wall.width - tex_x - 1;
	while (y <= draw_data.drawend)
	{
		d = ((y - (WIN_HEIGHT >> 1)) + (line_height >> 1)) << 8;
		tex_y = ((d * wall.height) / line_height) >> 8;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= wall.height)
			tex_y = wall.height - 1;
		if (tex_x < 0)
			tex_x = 0;
		if (tex_x >= wall.width)
			tex_x = wall.width - 1;
		pixel = wall.data + tex_y * wall.size_line +
		tex_x * (wall.bpp >> 3);
		color = *(int *)pixel;

		img_pixel_put(x, y, color, &game->main_img);
		y++;
	}
}

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

#include <stdint.h>

void	color_canvas(
	const char *addr,
	const int line_length)
{
	size_t		y;
	size_t		x;
	uint64_t	*pixel64;
	uint32_t	*row;

	y = 0;
	const uint64_t c64 = ((uint64_t)0x00FF00 << 32) | 0x00FF00;
	while (y <= WIN_HEIGHT)
	{
		row = (uint32_t *)(addr + y * line_length);
		x = 0;
		if (x & 1)
			row[x++] = 0x00FF00;
		pixel64 = (uint64_t *)(row + x);
		while (x + 1 <= WIN_WIDTH)
		{
			*pixel64++ = c64;
			x += 2;
		}
		while (x <= WIN_WIDTH)
			row[x++] = 0x00FF00;
		y++;
	}
}

#include <string.h>

int	raycast_loop(void *param)
{
	t_data		*game;
	int			x;
	t_ray		ray;
	t_hit		hit_data;
	t_draw		draw_data;
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
		game->fs_map = false;
		game->key_state->tab = false;
	}
	update_player(game, delta_time);
	// color_canvas(game->main_img.data, game->main_img.size_line);
	ft_memcpy(game->main_img.data, game->background.data, WIN_HEIGHT * game->background.size_line);
	// memcpy(game->main_img.data, game->background.data, WIN_HEIGHT * game->background.size_line);
	// ft_memset(game->main_img.data, 0, WIN_HEIGHT * game->main_img.size_line); 
	// draw_ceiling_and_floor(&game->main_img, 0xF00FFF, 0xFFFFFF);
	handle_cursor(game);
	while (x < WIN_WIDTH)
	{
		ray = init_ray(game->player, x);
		hit_data = cast_ray(game->map, &ray);
		draw_data = compute_draw_limits(hit_data.perpwalldist);
		draw_wall_slice(x, draw_data, game, ray, hit_data);
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
