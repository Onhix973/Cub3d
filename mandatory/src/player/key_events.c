/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:03:36 by tlutz             #+#    #+#             */
/*   Updated: 2025/11/28 16:16:24 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "cub3D.h"
#include "raycast.h"
#include <X11/keysym.h>
#include <stdlib.h>

void	handle_game_keys(t_key_state *key_state, int keycode)
{
	if (keycode == XK_w)
		key_state->w = true;
	if (keycode == XK_a)
		key_state->a = true;
	if (keycode == XK_s)
		key_state->s = true;
	if (keycode == XK_d)
		key_state->d = true;
	if (keycode == XK_Left)
		key_state->left = true;
	if (keycode == XK_Right)
		key_state->right = true;
	if (keycode == XK_Shift_L)
		key_state->shift = true;
}

int	key_press(int keycode, void *param)
{
	t_data	*game;

	game = (t_data *)param;
	if (keycode == XK_Escape)
		exit_game(game);
	else
		handle_game_keys(game->key_state, keycode);
	return (0);
}

int	key_release(int keycode, void *param)
{
	t_key_state	*key_state;

	key_state = (t_key_state *)param;
	if (keycode == XK_w)
		key_state->w = false;
	if (keycode == XK_a)
		key_state->a = false;
	if (keycode == XK_s)
		key_state->s = false;
	if (keycode == XK_d)
		key_state->d = false;
	if (keycode == XK_Left)
		key_state->left = false;
	if (keycode == XK_Right)
		key_state->right = false;
	if (keycode == XK_Shift_L)
		key_state->shift = false;
	return (0);
}
