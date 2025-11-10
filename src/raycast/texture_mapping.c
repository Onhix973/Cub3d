#include "cub3D.h"
#include "structs.h"
#include "raycast.h"
#include "math.h"

int	clamp(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

t_draw	compute_draw_limits(double proj_wall_hit_dist)
{
	t_draw	draw_data;

	draw_data.line_height = (int)(WIN_HEIGHT / proj_wall_hit_dist);
	draw_data.draw_start = -draw_data.line_height / 2 + WIN_HEIGHT / 2;
	if (draw_data.draw_start < 0)
		draw_data.draw_start = 0;
	draw_data.draw_end = draw_data.line_height / 2 + WIN_HEIGHT / 2;
	if (draw_data.draw_end >= WIN_HEIGHT)
		draw_data.draw_end = WIN_HEIGHT - 1;
	return (draw_data);
}

t_texture	get_wall_tex(t_hit *hit_data, t_ray *ray, t_data *game, \
	double *wall_hit_x)
{
	if (!hit_data->wall_tile_hit_side)
	{
		*wall_hit_x = game->player->pos.y + hit_data->proj_wall_hit_dist \
		* ray->dir_y;
		if (ray->dir_x > 0)
			return (game->e_wall);
		else
			return (game->w_wall);
	}
	else
	{
		*wall_hit_x = game->player->pos.x + hit_data->proj_wall_hit_dist \
		* ray->dir_x;
		if (ray->dir_y > 0)
			return (game->s_wall);
		else
			return (game->n_wall);
	}
}

static inline bool	check_flip_textures(t_hit *hit_data, t_ray *ray)
{
	return ((hit_data->wall_tile_hit_side == HORIZONTAL_HIT && ray->dir_x > 0) \
	|| (hit_data->wall_tile_hit_side == VERTICAL_HIT && ray->dir_y < 0));
}

void	draw_wall_slice(int win_x, t_data *game, t_ray *ray, t_hit *hit_data, t_player *pov)
{
	int				pixel_y;
	int				wall_slice_height;
	int				tex_pixel_pos;
	int				color;
	char			*tex_pixel;
	double			wall_hit_x;
	t_int_vector	tex;
	t_draw			draw_data;
	t_texture		wall;

	draw_data = compute_draw_limits(hit_data->proj_wall_hit_dist);
	pixel_y = draw_data.draw_start;
	wall_slice_height = draw_data.line_height;
	wall = get_wall_tex(hit_data, ray, game, &wall_hit_x);
	//TODO
	if (hit_data->wall_tile_hit_side == HORIZONTAL_HIT)
		wall_hit_x = pov->pos.y + hit_data->proj_wall_hit_dist * ray->dir_y;
	else
		wall_hit_x = pov->pos.x + hit_data->proj_wall_hit_dist * ray->dir_x;
	wall_hit_x -= floor(wall_hit_x);
	tex.x = (int)(wall_hit_x * (double)wall.width);
	if (check_flip_textures(hit_data, ray))
		tex.x = wall.width - tex.x - 1;
	if (wall_slice_height == 0)
		wall_slice_height = 1;
	while (pixel_y <= draw_data.draw_end)
	{
		tex_pixel_pos = ((pixel_y - (WIN_HEIGHT >> 1)) + (wall_slice_height >> 1)) << 8;
		tex.y = ((tex_pixel_pos * wall.height) / wall_slice_height) >> 8;
		tex.y = clamp(tex.y, 0, wall.height - 1);
		tex.x = clamp(tex.x, 0, wall.width - 1);
		tex_pixel = wall.data + tex.y * wall.size_line +
		tex.x * (wall.bpp >> 3);
		color = *(int *)tex_pixel;
		img_pixel_put(win_x, pixel_y, color, &game->main_img);
		pixel_y++;
	}
}

void	draw_portal_slice(int win_x, t_data *game, t_ray *ray, t_hit *hit_data, t_player *pov)
{
	int				pixel_y;
	int				portal_slice_height;
	int				tex_pixel_pos;
	int				color;
	char			*tex_pixel;
	double			portal_hit_x;
	t_int_vector	tex;
	t_draw			draw_data;

	draw_data = compute_draw_limits(hit_data->proj_wall_hit_dist);
	pixel_y = draw_data.draw_start;
	portal_slice_height = draw_data.line_height;
	if (hit_data->wall_tile_hit_side == HORIZONTAL_HIT)
		portal_hit_x = pov->pos.y + hit_data->proj_wall_hit_dist * ray->dir_y;
	else
		portal_hit_x = pov->pos.x + hit_data->proj_wall_hit_dist * ray->dir_x;
	portal_hit_x -= floor(portal_hit_x);
	tex.x = (int)(portal_hit_x * (double)game->portal.width);
	if ((hit_data->wall_tile_hit_side == HORIZONTAL_HIT && ray->dir_x > 0) 
	|| (hit_data->wall_tile_hit_side == VERTICAL_HIT && ray->dir_y < 0))
		tex.x = game->portal.width - tex.x - 1;
	tex.x = clamp(tex.x, 0, game->portal.width - 1);
	if (portal_slice_height == 0)
		portal_slice_height = 1;
	while (pixel_y <= draw_data.draw_end)
	{
		tex_pixel_pos = ((pixel_y - (WIN_HEIGHT >> 1)) + (portal_slice_height >> 1)) << 8;
		tex.y = ((tex_pixel_pos * game->portal.height) / portal_slice_height) >> 8;
		tex.y = clamp(tex.y, 0, game->portal.height);
		tex_pixel = game->portal.data + tex.y * game->portal.size_line + tex.x * (game->portal.bpp >> 3);
		color = *(int *)tex_pixel;
		if ((color & 0xFFFFFF) != 0)
			img_pixel_put(win_x, pixel_y, color, &game->main_img);
		pixel_y++;
	}
}
