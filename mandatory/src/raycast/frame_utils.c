/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:03:57 by tlutz             #+#    #+#             */
/*   Updated: 2025/11/28 16:55:56 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdlib.h>

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
