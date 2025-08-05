#include "raycast.h"
#include <math.h>

float dot_product(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y *v2.y);
}

float vector_length(t_vector v)
{
	return (sqrtf(v.x * v.x + v.y * v.y));
}
