/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:04:04 by tlutz             #+#    #+#             */
/*   Updated: 2025/11/28 15:48:35 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "structs.h"
#include "raycast.h"
#include "math.h"

int	compute_texture_x(double wall_hit_x, t_ray *ray, int tex_width)
{
	int	tex_x;

	wall_hit_x -= floor(wall_hit_x);
	tex_x = (int)(wall_hit_x * (double)tex_width);
	if (check_flip_textures(ray))
		tex_x = tex_width - tex_x - 1;
	return (clamp(tex_x, 0, tex_width - 1));
}

int	compute_texture_y(int pixel_y, int wall_slice_height, int tex_height)
{
	int	tex_pixel_pos;
	int	tex_y;

	tex_pixel_pos = ((pixel_y - (WIN_HEIGHT >> 1))
			+ (wall_slice_height >> 1)) << 8;
	tex_y = ((tex_pixel_pos * tex_height) / wall_slice_height) >> 8;
	return (clamp(tex_y, 0, tex_height - 1));
}

int	get_texture_color(int tex_x, int tex_y, t_tex *wall)
{
	char	*tex_pixel;

	tex_pixel = wall->data + tex_y * wall->size_line
		+ tex_x * (wall->bpp >> 3);
	return (*(int *)tex_pixel);
}

static	void	draw_textured_slice(int win_x, t_draw draw_data, t_data *game,
	t_ray *ray)
{
	t_int_vector	tex;
	int				pixel_y;
	int				wall_slice_height;
	t_tex			wall;
	double			wall_hit_x;

	if (draw_data.line_height == 0)
		wall_slice_height = 1;
	else
		wall_slice_height = draw_data.line_height;
	wall = get_wall_tex(ray, game, &wall_hit_x);
	tex.x = compute_texture_x(wall_hit_x, ray, wall.width);
	pixel_y = draw_data.draw_start;
	while (pixel_y <= draw_data.draw_end)
	{
		tex.y = compute_texture_y(pixel_y, wall_slice_height, wall.height);
		img_pixel_put(win_x, pixel_y, get_texture_color(tex.x, tex.y, &wall),
			&game->main_img);
		pixel_y++;
	}
}

void	draw_wall_slice(int win_x, t_data *game, t_ray *ray)
{
	t_draw	draw_data;

	draw_data = compute_draw_limits(ray->proj_wall_hit_dist);
	draw_textured_slice(win_x, draw_data, game, ray);
}
