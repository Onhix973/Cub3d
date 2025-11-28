/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_settings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:03:12 by tlutz             #+#    #+#             */
/*   Updated: 2025/11/28 15:03:13 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "structs.h"
#include "raycast.h"

static void	compute_fs_map_size(t_map_disp_set *map_settings)
{
	if (map_settings->map_width * FS_MAP_SCALE < WIN_WIDTH)
		map_settings->fs_map_width = map_settings->map_width * FS_MAP_SCALE;
	else
		map_settings->fs_map_width = WIN_WIDTH - 64;
	if (map_settings->map_height * FS_MAP_SCALE < WIN_HEIGHT)
		map_settings->fs_map_height = map_settings->map_height * FS_MAP_SCALE;
	else
		map_settings->fs_map_height = WIN_HEIGHT - 64;
	map_settings->fs_map_x = (WIN_WIDTH - map_settings->fs_map_width) / 2;
	map_settings->fs_map_y = (WIN_HEIGHT - map_settings->fs_map_height) / 2;
}

static void	init_map_settings(t_map_disp_set *map_settings, t_context *ctx)
{
	map_settings->map_width = ctx->map.width;
	map_settings->map_height = ctx->map.height;
	map_settings->minimap_width = WIN_WIDTH / 6.4f;
	map_settings->minimap_height = WIN_HEIGHT / 3.6f;
	map_settings->minimap_margin = map_settings->minimap_width / 10;
	compute_fs_map_size(map_settings);
}

static void	init_game_states(t_game_states *game_states)
{
	game_states->mouse_activated = false;
	game_states->fs_map = false;
	game_states->attack_state = false;
	game_states->inspect = false;
	game_states->block_state = false;
}

bool	init_game(t_data *game, t_context *ctx)
{
	init_game_states(&game->g_states);
	init_map_settings(&game->map_disp_set, ctx);
	init_player(game->player, ctx);
	if (!init_mlx_and_textures(game, ctx))
		return (false);
	if (!init_background_buffer(game, ctx))
		return (false);
	if (!init_spritesheets(game))
		return (false);
	return (true);
}
