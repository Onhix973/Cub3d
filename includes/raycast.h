#ifndef RAYCAST_H
# define RAYCAST_H

typedef struct s_vector
{
	float x;
	float y;
}	t_vector;

/*******************************Vectors Maths******************************** */


t_vector 	add_vectors(t_vector v1, t_vector v2);

t_vector 	substract_vectors(t_vector v1, t_vector v2);

float 		vector_length(t_vector v);

t_vector 	scalar_mult(t_vector v, float scalar);

t_vector 	normalize_vector(t_vector v);

float 		dot_product(t_vector v1, t_vector v2);

#endif