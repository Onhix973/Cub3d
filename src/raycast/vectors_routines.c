/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_routines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:04:07 by tlutz             #+#    #+#             */
/*   Updated: 2025/11/28 15:04:12 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include <math.h>
#include <stdlib.h>

t_vector	add_vectors(t_vector v1, t_vector v2)
{
	t_vector	new;

	new.x = v1.x + v2.x;
	new.y = v1.y + v2.y;
	return (new);
}

t_vector	substract_vectors(t_vector v1, t_vector v2)
{
	t_vector	new;

	new.x = v1.x - v2.x;
	new.y = v1.y - v2.y;
	return (new);
}

t_vector	scalar_mult(t_vector v, float scalar)
{
	t_vector	new;

	new.x = v.x * scalar;
	new.y = v.y * scalar;
	return (new);
}

t_vector	normalize_vector(t_vector v)
{
	t_vector	new;
	const float	v_length = vector_length(v);

	if (v_length == 0)
	{
		new.x = 0;
		new.y = 0;
	}
	else
	{
		new.x = v.x / v_length;
		new.y = v.y / v_length;
	}
	return (new);
}

t_vector	get_direction_from_angle(float angle)
{
	t_vector	direction;

	direction.x = cosf(angle);
	direction.y = -sinf(angle);
	return (direction);
}
