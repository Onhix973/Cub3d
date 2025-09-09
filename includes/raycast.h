#ifndef RAYCAST_H
# define RAYCAST_H

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

#include "structs.h"

int		exit_game(void *param);

/*******************************Init***************************************** */

bool	init_mlx_and_textures(t_data *game);

void	init_player(t_data *game, t_player *player);

/***************************Minimap System*********************************** */

void	draw_minimap_player(t_data *game);

void	update_fs_minimap_camera_offset(t_data *game);

void	draw_entire_minimap(t_data *game);

void 	update_minimap_camera_offset(t_data *game);

void 	draw_fs_minimap(t_data *game);

void	draw_fs_minimap_player(t_data *game);

// inline void	update_fs_map_camera(t_data *game);

/***************************Player moves and events************************** */

int 	update_player(t_data *game, float delta_time);

int		key_press(int keycode, void *param);

int		key_release(int keycode, void *param);

int 	mouse_handler(int x, int y, void *param);

int		focus_out_handler(t_data *game);

void 	rotate_vector(t_vector *v, float angle);

/*******************************Raycast/DDA********************************** */

int 	raycast_loop(void * param);

float	get_delta_time(void);

void 	img_pixel_put(int x, int y, int color, t_data *game);

void	find_dist_to_nearest_tile(t_player *player, t_ray *ray);

t_ray	init_ray(t_player *player, int x);

t_hit	find_wall_side(t_hit hit_data, t_ray *ray);

t_hit	cast_ray(char **map, t_ray *ray);

/*******************************Vectors Maths******************************** */

t_vector 	add_vectors(t_vector v1, t_vector v2);

t_vector 	substract_vectors(t_vector v1, t_vector v2);

float 		vector_length(t_vector v);

t_vector 	scalar_mult(t_vector v, float scalar);

t_vector 	normalize_vector(t_vector v);

float 		dot_product(t_vector v1, t_vector v2);

t_vector 	get_direction_from_angle(float angle);

#endif