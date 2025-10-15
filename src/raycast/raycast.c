#include "raycast.h"
#include "cub3D.h"
#include "libft.h"
#include "mlx.h"
#include <math.h>
#include <stdio.h>

//TODO
#include <string.h>


void draw_portal_slice(int win_x, t_data *game, t_ray *ray, t_hit *hit_data)
{
    int pixel_y;
    int wall_slice_height;
    int tex_pixel_pos;
    unsigned int color;
    char *tex_pixel;
    double wall_hit_x;
    t_int_vector tex;
    t_draw draw_data;

    draw_data = compute_draw_limits(hit_data->proj_wall_hit_dist);
    pixel_y = draw_data.draw_start;
    wall_slice_height = draw_data.line_height;
    if (hit_data->wall_tile_hit_side == HORIZONTAL_HIT)
        wall_hit_x = game->player->pos.y + hit_data->proj_wall_hit_dist * ray->dir_y;
    else
        wall_hit_x = game->player->pos.x + hit_data->proj_wall_hit_dist * ray->dir_x;
    wall_hit_x -= floor(wall_hit_x);
    tex.x = (int)(wall_hit_x * (double)game->portal.width);
    if ((hit_data->wall_tile_hit_side == HORIZONTAL_HIT && ray->dir_x > 0) ||
        (hit_data->wall_tile_hit_side == VERTICAL_HIT && ray->dir_y < 0))
        tex.x = game->portal.width - tex.x - 1;
    tex.x = clamp(tex.x, 0, game->portal.width - 1);
    while (pixel_y <= draw_data.draw_end)
    {
        tex_pixel_pos = ((pixel_y - (WIN_HEIGHT >> 1)) + (wall_slice_height >> 1)) << 8;
        tex.y = ((tex_pixel_pos * game->portal.height) / wall_slice_height) >> 8;
    	tex.y = clamp(tex.y, 0, game->portal.height - 1);
        tex_pixel = game->portal.data + tex.y * game->portal.size_line + tex.x * (game->portal.bpp >> 3);
        memcpy(&color, tex_pixel, sizeof(unsigned int));
		if ((color & 0xFFFFFF) != 0)
			img_pixel_put(win_x, pixel_y, color, &game->main_img);
        pixel_y++;
    }
}

void	update_sprite_sheet(t_sprite_sheet *anim, float delta_time)
{
	anim->elapsed_time += delta_time;
	if (anim->elapsed_time >= anim->frame_time)
	{
		if (anim->looped)
			anim->curr_frame = (anim->curr_frame + 1) % anim->num_frames;
		else
		{
			if (anim->curr_frame < anim->num_frames - 1)
				anim->curr_frame++;
		}
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
	if (game->key_state->c && !game->mouse_activated)
	{
		XFixesHideCursor(game->display, game->main_win);
		XFlush(game->display);
		game->mouse_activated = true;
	}
	else if (game->key_state->v && game->mouse_activated)
	{
		XFixesShowCursor(game->display, game->main_win);
		XFlush(game->display);
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

bool	is_player_moving(t_key_state *key_state)
{
	if (key_state->w || key_state->s || key_state->a || key_state->d)
		return (true);
	return (false);
}

void	select_animation(t_data *game, float delta_time)
{
	if (game->attack_state)
	{
		update_sprite_sheet(game->attack, delta_time);
		draw_sprite_sheet_anim(game->attack, &game->main_img);
		if (!game->attack->looped && game->attack->curr_frame == game->attack->num_frames - 1)
			game->attack_state = false;
	}
	else if (game->block_state)
	{
		update_sprite_sheet(game->block, delta_time);
		draw_sprite_sheet_anim(game->block, &game->main_img);
		if (!game->block->looped && game->block->curr_frame == game->block->num_frames - 1)
			game->block_state = false;
	}
	else if (game->inspect)
	{
		update_sprite_sheet(game->lookat, delta_time);
		draw_sprite_sheet_anim(game->lookat, &game->main_img);
		if (!game->lookat->looped && game->lookat->curr_frame == game->lookat->num_frames - 1)
			game->inspect = false;
	}
	else if (is_player_moving(game->key_state) && game->key_state->shift)
	{
		update_sprite_sheet(game->run, delta_time);
		draw_sprite_sheet_anim(game->run, &game->main_img);
	}
	else if (is_player_moving(game->key_state))
	{
		update_sprite_sheet(game->walk, delta_time);
		draw_sprite_sheet_anim(game->walk, &game->main_img);
	}
	else
	{
		update_sprite_sheet(game->idle, delta_time);
		draw_sprite_sheet_anim(game->idle, &game->main_img);
	}
}

void	create_portal(t_data *game, t_ray *ray, t_hit *hit, t_portal *portal)
{
	portal->active = true;
	portal->map_x = ray->map_tile.x;
	portal->map_y = ray->map_tile.y;
	portal->side = hit->wall_tile_hit_side;
	if (hit->wall_tile_hit_side == HORIZONTAL_HIT)
	{
		if (ray->dir_x < 0)
		{
			portal->world_x = ray->map_tile.x + 1.0f;
			portal->graphical_facing = WEST;
			portal->facing = EAST;
		}
		else
		{
			portal->world_x = (float)ray->map_tile.x;
			portal->graphical_facing = EAST;
			portal->facing = WEST;
		}
		portal->world_y = game->player->pos.y + ray->dir_y * hit->proj_wall_hit_dist;
	}
	else if (hit->wall_tile_hit_side == VERTICAL_HIT)
	{
		if (ray->dir_y < 0)
		{
			portal->world_y = ray->map_tile.y + 1.0f;
			portal->graphical_facing = NORTH;
			portal->facing = SOUTH;
		}
		else
		{
			portal->world_y = (float)ray->map_tile.y;
			portal->graphical_facing = SOUTH;
			portal->facing = NORTH;
		}
		portal->world_x = game->player->pos.x + ray->dir_x * hit->proj_wall_hit_dist;
	}
	printf("PORTAL CREATED AT : %d, %d\n", portal->map_x, portal->map_y);
}

bool	check_for_portal(t_portal *portal, t_ray *ray, t_hit *hit_data)
{
	bool	is_portal_slice;

	is_portal_slice = false;
	if (portal->active && ray->map_tile.x == portal->map_x \
	&& ray->map_tile.y == portal->map_y \
	&& hit_data->wall_tile_hit_side == portal->side)
	{
		if (portal->side == HORIZONTAL_HIT)
		{
			if ((portal->graphical_facing == WEST && ray->dir_x < 0)\
			|| (portal->graphical_facing == EAST && ray->dir_x > 0))
				is_portal_slice = true;
		}
		else if (portal->side == VERTICAL_HIT)
		{
			if ((portal->graphical_facing == NORTH && ray->dir_y < 0)\
			|| (portal->graphical_facing == SOUTH && ray->dir_y > 0))
				is_portal_slice = true;
		}
	}
	return (is_portal_slice);
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
		game->lookat->curr_frame = 0;
	}
	if (game->key_state->e && !game->attack_state && !game->block_state && !game->inspect)
	{
		game->key_state->e = false;
		game->attack_state = true;
		game->attack_triggered = true;
		game->attack->curr_frame = 0;
	}
	if (game->key_state->q && !game->block_state && !game->attack_state && !game->inspect)
	{
		game->key_state->q = false;
		game->block_state = true;
		game->block->curr_frame = 0;
	}
	game->player->prev_pos = game->player->pos;
	update_player(game, delta_time);
	teleport_player_crossing_portal(game);
	// ft_memcpy(game->main_img.data, game->background.data, WIN_HEIGHT * game->background.size_line);
	//TODO REMOVE MEMCPY
	memcpy(game->main_img.data, game->background.data, WIN_HEIGHT * game->background.size_line);
	handle_cursor(game);
	while (x < WIN_WIDTH)
	{
		ray = init_ray(game->player, x);
		hit_data = cast_ray(game->map, &ray);
		if (game->attack_triggered)
		{
			if (x == WIN_WIDTH >> 1)
			{
				if ((hit_data.wall_tile_hit_side == VERTICAL_HIT \
					|| hit_data.wall_tile_hit_side == HORIZONTAL_HIT) && hit_data.proj_wall_hit_dist < MAX_PORTAL_RANGE)
				{
					if (!game->portals.a.active)
					{
						create_portal(game, &ray, &hit_data, &game->portals.a);
						game->portals.a.active = true;
					}
					else if (!game->portals.b.active)
					{
						create_portal(game, &ray, &hit_data, &game->portals.b);
						game->portals.b.active = true;
						game->portals.linked = true;
					}
				}
				game->attack_triggered = false;
			}
		}
		bool	is_portal_slice = false;
		is_portal_slice = check_for_portal(&game->portals.a, &ray, &hit_data) \
		|| check_for_portal(&game->portals.b, &ray, &hit_data);
		draw_wall_slice(x, game, &ray, &hit_data);
		if (is_portal_slice)
			draw_portal_slice(x, game, &ray, &hit_data);
		x++;
	}
	draw_crosshair(game);
	select_animation(game, delta_time);
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
