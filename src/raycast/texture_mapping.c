#include "cub3D.h"
#include "structs.h"
#include "raycast.h"
#include "math.h"

static inline bool	check_flip_textures(t_ray *ray)
{
	return ((ray->wall_tile_hit_side == HORIZONTAL_HIT && ray->dir.x > 0) \
	|| (ray->wall_tile_hit_side == VERTICAL_HIT && ray->dir.y < 0));
}

//TODO Rework
void	draw_wall_slice(int win_x, t_data *game, t_ray *ray)
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

	draw_data = compute_draw_limits(ray->proj_wall_hit_dist);
	pixel_y = draw_data.draw_start;
	wall_slice_height = draw_data.line_height;
	wall = get_wall_tex(ray, game, &wall_hit_x);
	wall_hit_x -= floor(wall_hit_x);
	tex.x = (int)(wall_hit_x * (double)wall.width);
	if (check_flip_textures(ray))
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

//TODO Rework
void	draw_portal_slice(int win_x, t_data *game, t_ray *ray)
{
	int				pixel_y;
	int				portal_slice_height;
	int				tex_pixel_pos;
	int				color;
	char			*tex_pixel;
	double			portal_hit_x;
	t_int_vector	tex;
	t_draw			draw_data;

	draw_data = compute_draw_limits(ray->proj_wall_hit_dist);
	pixel_y = draw_data.draw_start;
	portal_slice_height = draw_data.line_height;
	if (!ray->wall_tile_hit_side)
		portal_hit_x = game->player->pos.y + ray->proj_wall_hit_dist * ray->dir.y;
	else
		portal_hit_x = game->player->pos.x + ray->proj_wall_hit_dist *ray->dir.x;
	portal_hit_x -= floor(portal_hit_x);
	tex.x = (int)(portal_hit_x * (double)game->portal.width);
	if ((ray->wall_tile_hit_side == HORIZONTAL_HIT && ray->dir.x > 0) 
	|| (ray->wall_tile_hit_side == VERTICAL_HIT && ray->dir.y < 0))
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
