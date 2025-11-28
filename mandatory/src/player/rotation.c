/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:03:39 by tlutz             #+#    #+#             */
/*   Updated: 2025/11/28 16:43:15 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "structs.h"
#include "raycast.h"
#include <math.h>
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
	return (0);
}
