/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:04:36 by tlutz             #+#    #+#             */
/*   Updated: 2025/11/28 15:04:53 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "raycast.h"
#include "mlx.h"
#include "libft.h"
#include <stdlib.h>

int	mouse_hook(int button, int x, int y, void *param)
{
	t_data	*game;

	(void)y;
	(void)x;
	game = (t_data *)param;
	if (button == 1)
	{
		if (!game->g_states.attack_state && !game->g_states.block_state
			&& !game->g_states.inspect)
		{
			game->g_states.attack_state = true;
			game->g_states.attack_triggered = true;
			game->anims.attack.curr_frame = 0;
		}
	}
	else if (button == 3)
	{
		if (!game->g_states.block_state && !game->g_states.attack_state
			&& !game->g_states.inspect)
		{
			game->g_states.block_state = true;
			game->anims.block.curr_frame = 0;
		}
	}
	return (0);
}

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
	mlx_mouse_hook(game.win, mouse_hook, &game);
	mlx_loop_hook(game.mlx, &game_loop, &game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
