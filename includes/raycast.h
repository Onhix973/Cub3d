#ifndef RAYCAST_H
# define RAYCAST_H

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

#include "structs.h"

/*******************************Raycast/DDA********************************** */

int 		raycast_loop(void * param);


/*******************************Vectors Maths******************************** */

t_vector 	add_vectors(t_vector v1, t_vector v2);

t_vector 	substract_vectors(t_vector v1, t_vector v2);

float 		vector_length(t_vector v);

t_vector 	scalar_mult(t_vector v, float scalar);

t_vector 	normalize_vector(t_vector v);

float 		dot_product(t_vector v1, t_vector v2);

t_vector 	get_direction_from_angle(float angle);

#endif