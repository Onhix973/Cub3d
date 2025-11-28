/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping_portals.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:04:03 by tlutz             #+#    #+#             */
/*   Updated: 2025/11/28 15:04:03 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "cub3D.h"
#include "raycast.h"
#include <math.h>

static double	compute_portal_hit_position(t_ray *ray, t_data *game)
{
	double	portal_hit_x;

	if (!ray->wall_tile_hit_side)
		portal_hit_x = game->player->pos.y + ray->proj_wall_hit_dist
			* ray->dir.y;
	else
		portal_hit_x = game->player->pos.x + ray->proj_wall_hit_dist
			* ray->dir.x;
	return (portal_hit_x);
}

static void	draw_textured_portal_slice(int win_x, t_draw draw_data,
	t_data *game, t_ray *ray)
{
	t_int_vector	tex;
	int				pixel_y;
	int				portal_slice_height;
	double			portal_hit_x;
	int				color;

	if (draw_data.line_height == 0)
		portal_slice_height = 1;
	else
		portal_slice_height = draw_data.line_height;
	portal_hit_x = compute_portal_hit_position(ray, game);
	tex.x = compute_texture_x(portal_hit_x, ray, game->portal.width);
	pixel_y = draw_data.draw_start;
	while (pixel_y <= draw_data.draw_end)
	{
		tex.y = compute_texture_y(pixel_y, portal_slice_height,
				game->portal.height);
		color = get_texture_color(tex.x, tex.y, &game->portal);
		if ((color & 0xFFFFFF) != 0)
			img_pixel_put(win_x, pixel_y, color, &game->main_img);
		pixel_y++;
	}
}

void	draw_portal_slice(int win_x, t_data *game, t_ray *ray)
{
	t_draw	draw_data;

	draw_data = compute_draw_limits(ray->proj_wall_hit_dist);
	draw_textured_portal_slice(win_x, draw_data, game, ray);
}
