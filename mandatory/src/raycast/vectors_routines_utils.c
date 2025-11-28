/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_routines_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:04:06 by tlutz             #+#    #+#             */
/*   Updated: 2025/11/28 15:04:06 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include <math.h>

float	dot_product(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}

float	vector_length(t_vector v)
{
	return (sqrtf(v.x * v.x + v.y * v.y));
}

int	clamp(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

void	rotate_vector(t_vector *v, float angle)
{
	float	oldx;

	oldx = v->x;
	v->x = v->x * cosf(angle) - v->y * sinf(angle);
	v->y = oldx * sinf(angle) + v->y * cosf(angle);
}
