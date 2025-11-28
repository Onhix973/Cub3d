/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:04:01 by tlutz             #+#    #+#             */
/*   Updated: 2025/11/28 16:58:25 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include "cub3D.h"
#include "libft.h"
#include "mlx.h"
#include <math.h>

void	game_loop_display_wrapper(t_data *game)
{
	draw_crosshair(game);
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
	update_player(game, delta_time);
	ft_memcpy(game->main_img.data, game->background.data, WIN_HEIGHT
		* game->background.size_line);
	while (x < WIN_WIDTH)
	{
		ray = init_ray(game->player, x);
		cast_ray(game->map, &ray);
		draw_wall_slice(x, game, &ray);
		x++;
	}
	game_loop_display_wrapper(game);
	return (0);
}
