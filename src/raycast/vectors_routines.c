#include "raycast.h"
#include "math.h"

t_vector add_vectors(t_vector v1, t_vector v2)
{
	t_vector new;

	new.x = v1.x + v2.x;
	new.y = v2.x + v2.y;
	return (new);
}

t_vector substract_vectors(t_vector v1, t_vector v2)
{
	t_vector new;

	new.x = v1.x - v2.x;
	new.y = v2.x - v2.y;
	return (new);
}

float vector_length(t_vector v)
{
	return (sqrtf(v.x * v.x + v.y * v.y));
}

t_vector scalar_mult(t_vector v, float scalar)
{
	t_vector new;
	new.x = new.x * scalar;
	new.y = new.y * scalar;
	return (new);
}

t_vector normalize_vector(t_vector v)
{
	t_vector new;
	const float v_length = vector_length(v);

	new.x = new.x / v_length;
	new.y = new.y / v_length;
	return (new);
}

float dot_product(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y *v2.y);
}

