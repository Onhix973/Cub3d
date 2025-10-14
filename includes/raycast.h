#ifndef RAYCAST_H
# define RAYCAST_H

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

#define HORIZONTAL_HIT 0
#define VERTICAL_HIT 1

#include "structs.h"

int		exit_game(void *param);
//TODO
int	clamp(int value, int min, int max);


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

/***************************Player moves and events************************** */

int 	update_player(t_data *game, float delta_time);

int		key_press(int keycode, void *param);

int		key_release(int keycode, void *param);

int 	mouse_handler(int x, int y, void *param);

int		focus_out_handler(t_data *game);

void 	rotate_vector(t_vector *v, float angle);

bool	horizontal_hitboxes_checker(t_data *game, float new_x);

bool	vertical_hitboxes_checker(t_data *game, float new_x);

/*******************************Raycast/DDA********************************** */

int 	raycast_loop(void * param);

float	get_delta_time(void);

void 	img_pixel_put(int x, int y, int color, t_img *img);

void	find_dist_to_nearest_tile(t_player *player, t_ray *ray);

t_ray	init_ray(t_player *player, int x);

t_hit	cast_ray(char **map, t_ray *ray);

void	draw_ceiling_and_floor(t_img *img, int ceiling_color, int floor_color);

/*****************************Texture Mapping******************************** */

t_draw	compute_draw_limits(double proj_wall_hit_dist);

void	draw_wall_slice(int x, t_data *game, t_ray *ray, t_hit *hit_data);

void	img_pixel_put(int x, int y, int color, t_img *img);

/*******************************Vectors Maths******************************** */

t_vector 	add_vectors(t_vector v1, t_vector v2);

t_vector 	substract_vectors(t_vector v1, t_vector v2);

float 		vector_length(t_vector v);

t_vector 	scalar_mult(t_vector v, float scalar);

t_vector 	normalize_vector(t_vector v);

float 		dot_product(t_vector v1, t_vector v2);

t_vector 	get_direction_from_angle(float angle);

#endif