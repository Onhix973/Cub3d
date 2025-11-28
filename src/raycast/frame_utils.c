/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:03:57 by tlutz             #+#    #+#             */
/*   Updated: 2025/11/28 15:03:58 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "structs.h"
#include "cub3D.h"
#include "libft.h"
#include <stdlib.h>
#include "mlx.h"

float	get_delta_time(void)
{
	static struct timeval	last_time = {0, 0};
	struct timeval			current_time;
	float					delta;

	delta = 0.0f;
	gettimeofday(&current_time, NULL);
	if (last_time.tv_sec != 0 || last_time.tv_usec != 0)
	{
		delta = (current_time.tv_sec - last_time.tv_sec)
			+ (current_time.tv_usec - last_time.tv_usec) / 1000000.0f;
	}
	last_time = current_time;
	return (delta);
}

static void	update_fps_display(char *fps_display, int fps)
{
	char	*fps_str;
	int		i;
	int		j;

	i = 0;
	fps_str = ft_itoa(fps);
	while (i < 6)
	{
		fps_display[i] = "FPS : "[i];
		i++;
	}
	j = 0;
	while (fps_str[j])
	{
		fps_display[i] = fps_str[j];
		i++;
		j++;
	}
	fps_display[i] = '\0';
	free(fps_str);
}

void	fps_counter(float delta_time, t_data *game)
{
	static float	elapsed_time = 0.0f;
	static int		frame_count = 0;
	static int		fps = 0;
	static char		fps_display[32] = "FPS : 0";

	elapsed_time += delta_time;
	frame_count++;
	if (elapsed_time >= 1.0f)
	{
		fps = frame_count / elapsed_time;
		update_fps_display(fps_display, fps);
		elapsed_time = 0.0f;
		frame_count = 0;
	}
	mlx_string_put(game->mlx, game->win, WIN_WIDTH - 80, 50, 0xFFFFFF,
		fps_display);
}
