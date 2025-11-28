/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:03:14 by tlutz             #+#    #+#             */
/*   Updated: 2025/11/28 16:43:03 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "cub3D.h"
#include "raycast.h"
#include "parsing.h"
#include "mlx.h"

static bool	init_textures_data(t_data *game)
{
	game->n_wall.data = mlx_get_data_addr(game->n_wall.texture,
			&game->n_wall.bpp, &game->n_wall.size_line, &game->n_wall.endian);
	if (!game->n_wall.data)
		return (write_error(DATA_IMG_ERR));
	game->w_wall.data = mlx_get_data_addr(game->w_wall.texture,
			&game->w_wall.bpp, &game->w_wall.size_line, &game->w_wall.endian);
	if (!game->w_wall.data)
		return (write_error(DATA_IMG_ERR));
	game->e_wall.data = mlx_get_data_addr(game->e_wall.texture,
			&game->e_wall.bpp, &game->e_wall.size_line, &game->e_wall.endian);
	if (!game->e_wall.data)
		return (write_error(DATA_IMG_ERR));
	game->s_wall.data = mlx_get_data_addr(game->s_wall.texture,
			&game->s_wall.bpp, &game->s_wall.size_line, &game->s_wall.endian);
	if (!game->s_wall.data)
		return (write_error(DATA_IMG_ERR));
	return (true);
}

static bool	init_textures(t_data *game, t_context *ctx)
{
	game->n_wall.texture = mlx_xpm_file_to_image(game->mlx, ctx->conf.path[NO],
			&game->n_wall.width, &game->n_wall.height);
	if (!game->n_wall.texture)
		return (write_error(IMAGE_LOAD_ERR));
	game->s_wall.texture = mlx_xpm_file_to_image(game->mlx, ctx->conf.path[SO],
			&game->s_wall.width, &game->s_wall.height);
	if (!game->s_wall.texture)
		return (write_error(IMAGE_LOAD_ERR));
	game->w_wall.texture = mlx_xpm_file_to_image(game->mlx, ctx->conf.path[WE],
			&game->w_wall.width, &game->w_wall.height);
	if (!game->w_wall.texture)
		return (write_error(IMAGE_LOAD_ERR));
	game->e_wall.texture = mlx_xpm_file_to_image(game->mlx, ctx->conf.path[EA],
			&game->e_wall.width, &game->e_wall.height);
	if (!game->e_wall.texture)
		return (write_error(IMAGE_LOAD_ERR));
	if (!init_textures_data(game))
		return (false);
	return (true);
}

bool	init_mlx_and_textures(t_data *game, t_context *ctx)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (write_error(MLX_INIT_ERR));
	game->main_img.ptr = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->main_img.ptr)
		return (write_error(IMAGE_CREATION_ERR));
	game->main_img.data = mlx_get_data_addr(game->main_img.ptr,
			&game->main_img.bpp, &game->main_img.size_line,
			&game->main_img.endian);
	if (!game->main_img.data)
		return (write_error(DATA_IMG_ERR));
	if (!init_textures(game, ctx))
		return (false);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!game->win)
		return (write_error(MLX_WINDOW_ERR));
	mlx_hook(game->win, KeyPress, KeyPressMask, key_press, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, key_release,
		game->key_state);
	mlx_hook(game->win, FocusOut, FocusChangeMask, focus_out_handler, game);
	mlx_hook(game->win, DestroyNotify, NoEventMask, exit_game, game);
	return (true);
}

bool	init_background_buffer(t_data *game, t_context *ctx)
{
	game->background.ptr = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->background.ptr)
		return (write_error(IMAGE_CREATION_ERR));
	game->background.data = mlx_get_data_addr(game->background.ptr,
			&game->background.bpp, &game->background.size_line,
			&game->background.endian);
	if (!game->background.data)
	{
		mlx_destroy_image(game->mlx, game->background.ptr);
		return (write_error(DATA_IMG_ERR));
	}
	draw_ceiling_and_floor(&game->background,
		ctx->conf.ceil_hex, ctx->conf.floor_hex);
	return (true);
}
