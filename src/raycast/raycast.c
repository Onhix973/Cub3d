#include "raycast.h"
#include "cub3D.h"
#include "libft.h"
#include "mlx.h"
#include <math.h>
#include <stdio.h>

void	update_sprite_sheet(t_sprite_sheet *anim, float delta_time)
{
	anim->elapsed_time += delta_time;
	if (anim->elapsed_time >= anim->frame_time)
	{
		anim->curr_frame = (anim->curr_frame + 1) % anim->num_frames;
		anim->elapsed_time = 0;
	}
}

void	blit_frame(t_img *sheet, int sx, int sy, int w, int h, t_img *target, int dx, int dy)
{
	char	*data_sheet;
	int		x;
	int		y;
	int		src_pos;
	unsigned int pixel_color;
	int		dst_pos;

	y = 0;
	data_sheet = mlx_get_data_addr(sheet->ptr, &sheet->bpp, &sheet->size_line, &sheet->endian);
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			src_pos = (sy + y) * sheet->size_line + (sx + x) * (sheet->bpp / 8);
			dst_pos = (dy + y) * target->size_line + (dx + x) * (target->bpp / 8);
			pixel_color = *(unsigned int *)(data_sheet + src_pos);
			if ((pixel_color & 0xFFFFFF) != 0)
				*(unsigned int *)(target->data + dst_pos) = pixel_color;
			x++;
		}
		y++;
	}
}

void	draw_sprite_sheet_anim(t_sprite_sheet *anim, t_img *screen)
{
	int	frame_x = (anim->curr_frame % anim->frames_per_row) * anim->frame_w;
	int	frame_y = (anim->curr_frame / anim->frames_per_row) * anim->frame_h;
	blit_frame(&anim->sheet, frame_x, frame_y, anim->frame_w, anim->frame_h, screen, anim->x, anim->y);
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

// #include <stdio.h>
// void	fps_counter(float delta_time)
// {
// 	static float elapsed_time = 0.0f;
// 	static int frame_count = 0;
// 	static int fps = 0;

// 	elapsed_time += delta_time;
// 	frame_count++;

// 	if (elapsed_time >= 1.0f)
// 	{
// 		fps = frame_count / elapsed_time;
// 		elapsed_time = 0.0f;
// 		frame_count = 0;
// 	}
// 	if (fps)
// 		printf("FPS: %d\n", fps);
// }

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

void	color_canvas(const char *addr, const int line_length)
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

#include <sys/time.h>

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
	if (game->key_state->l && !game->inspect)
	{
		game->key_state->l = false;
		game->inspect = true;
	}
	else if (game->key_state->l && game->inspect)
	{
		game->key_state->l = false;
		game->inspect = false;
	}
	update_player(game, delta_time);
	// color_canvas(game->main_img.data, game->main_img.size_line);
	ft_memcpy(game->main_img.data, game->background.data, WIN_HEIGHT * game->background.size_line);
	handle_cursor(game);
	while (x < WIN_WIDTH)
	{
		ray = init_ray(game->player, x);
		hit_data = cast_ray(game->map, &ray);
		draw_wall_slice(x, game, &ray, &hit_data);
		x++;
	}
	draw_crosshair(game);
	if (game->inspect)
	{
		update_sprite_sheet(game->lookat, delta_time);
		draw_sprite_sheet_anim(game->lookat, &game->main_img);
		static int old_frame = 0;
		if (old_frame == game->lookat->num_frames - 1 && game->lookat->curr_frame == 0)
			game->inspect = false;
		old_frame = game->lookat->curr_frame;
	}
	else if (game->key_state->w || game->key_state->s || game->key_state->a || game->key_state->d)
	{
		update_sprite_sheet(game->anim, delta_time);
		draw_sprite_sheet_anim(game->anim, &game->main_img);
	}
	else
	{
		update_sprite_sheet(game->idle, delta_time);
		draw_sprite_sheet_anim(game->idle, &game->main_img);
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
	mlx_put_image_to_window(game->mlx, game->win, game->main_img.ptr, 0, 0);
	fps_counter(delta_time, game);
	return (0);
}
