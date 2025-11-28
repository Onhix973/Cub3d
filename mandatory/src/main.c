/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:04:36 by tlutz             #+#    #+#             */
/*   Updated: 2025/11/28 16:05:17 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "raycast.h"
#include "mlx.h"
#include "libft.h"
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_context	ctx;
	t_data		game;
	t_player	player;
	t_key_state	key_states;

	ft_memset(&game, 0, sizeof(t_data));
	ft_memset(&key_states, 0, sizeof(t_key_state));
	context_creator(argc, argv, &ctx);
	game.player = &player;
	game.map = ctx.map.grid;
	game.key_state = &key_states;
	game.map_width = ctx.map.width;
	game.map_height = ctx.map.height;
	if (!init_game(&game, &ctx))
	{
		context_free(&ctx, false);
		exit_error(&game);
	}
	context_free(&ctx, false);
	mlx_loop_hook(game.mlx, &game_loop, &game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
