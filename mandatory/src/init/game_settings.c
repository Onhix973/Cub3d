/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_settings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:03:12 by tlutz             #+#    #+#             */
/*   Updated: 2025/11/28 16:06:26 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "structs.h"
#include "raycast.h"

bool	init_game(t_data *game, t_context *ctx)
{
	init_player(game->player, ctx);
	if (!init_mlx_and_textures(game, ctx))
		return (false);
	if (!init_background_buffer(game, ctx))
		return (false);
	return (true);
}
