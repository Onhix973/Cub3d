/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:03:55 by tlutz             #+#    #+#             */
/*   Updated: 2025/11/28 15:33:59 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "raycast.h"
#include "cub3D.h"

bool	check_flip_textures(t_ray *ray)
{
	return ((ray->wall_tile_hit_side == HORIZONTAL_HIT && ray->dir.x > 0)
		|| (ray->wall_tile_hit_side == VERTICAL_HIT && ray->dir.y < 0));
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

t_tex	get_wall_tex(t_ray *ray, t_data *game,
	double *wall_hit_x)
{
	if (!ray->wall_tile_hit_side)
	{
		*wall_hit_x = game->player->pos.y + ray->proj_wall_hit_dist
			* ray->dir.y;
		if (ray->dir.x > 0)
			return (game->w_wall);
		else
			return (game->e_wall);
	}
	else
	{
		*wall_hit_x = game->player->pos.x + ray->proj_wall_hit_dist
			* ray->dir.x;
		if (ray->dir.y > 0)
			return (game->n_wall);
		else
			return (game->s_wall);
	}
}
