/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:03:39 by tlutz             #+#    #+#             */
/*   Updated: 2025/11/28 15:03:40 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "structs.h"
#include "raycast.h"
#include <math.h>
#include <X11/extensions/Xfixes.h>
#include "mlx.h"

int	focus_out_handler(t_data *game)
{
	game->key_state->w = false;
	game->key_state->a = false;
	game->key_state->s = false;
	game->key_state->d = false;
	game->key_state->left = false;
	game->key_state->right = false;
	game->key_state->shift = false;
	game->key_state->c = false;
	game->key_state->v = false;
	if (game->g_states.mouse_activated)
	{
		game->g_states.mouse_activated = false;
		XFixesShowCursor(game->display, game->main_win);
		XFlush(game->display);
	}
	return (0);
}

int	mouse_handler(int x, int y, void *param)
{
	t_data		*game;
	static int	ignore_mouse_event = 0;
	int			delta_x;
	float		angle;

	(void)y;
	game = (t_data *)param;
	if (!game->g_states.mouse_activated)
		return (0);
	if (ignore_mouse_event)
	{
		ignore_mouse_event = 0;
		return (0);
	}
	delta_x = x - WIN_WIDTH * 0.5;
	angle = delta_x * MOUSE_SENSITIVITY;
	rotate_vector(&game->player->dir, angle);
	rotate_vector(&game->player->camera_plane, angle);
	mlx_mouse_move(game->mlx, game->win, WIN_WIDTH * 0.5, WIN_HEIGHT * 0.5);
	ignore_mouse_event = 1;
	return (0);
}
