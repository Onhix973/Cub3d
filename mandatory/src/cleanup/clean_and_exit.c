/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:02:53 by tlutz             #+#    #+#             */
/*   Updated: 2025/11/28 16:17:39 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "cub3D.h"
#include "raycast.h"
#include "mlx.h"
#include <stdlib.h>

void	img_annihilator(void *mlx, void *img)
{
	if (!img)
		return ;
	mlx_destroy_image(mlx, img);
}

void	destroy_textures(t_data *game)
{
	img_annihilator(game->mlx, game->n_wall.texture);
	img_annihilator(game->mlx, game->e_wall.texture);
	img_annihilator(game->mlx, game->w_wall.texture);
	img_annihilator(game->mlx, game->s_wall.texture);
	img_annihilator(game->mlx, game->main_img.ptr);
	img_annihilator(game->mlx, game->background.ptr);
}

void	exit_error(t_data *game)
{
	destroy_textures(game);
	if (game->mlx && game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (game->map)
		free_tab(game->map);
	exit(EXIT_FAILURE);
}

int	exit_game(void *param)
{
	t_data	*game;

	game = (t_data *)param;
	destroy_textures(game);
	if (game->mlx && game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (game->map)
		free_tab(game->map);
	exit(EXIT_SUCCESS);
}
