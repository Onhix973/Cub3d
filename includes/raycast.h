#ifndef RAYCAST_H
# define RAYCAST_H

//TODO
#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

# define HORIZONTAL_HIT 0
# define VERTICAL_HIT 1

#include "structs.h"

/*******************************Cleanup************************************** */

int		exit_game(void *param);

void	exit_error(t_data *game);

void	free_tab(char **tab);

/*******************************Utils**************************************** */

int	clamp(int value, int min, int max);

int	color_chooser(t_data *game, t_int_vector m);

/*******************************Init***************************************** */

void	init_player(t_player *player, t_context *ctx);

bool	init_spritesheets(t_data* game);

bool	init_game(t_data *game, t_context *ctx);

bool	init_mlx_and_textures(t_data *game, t_context *ctx);

bool	init_background_buffer(t_data *game, t_context *ctx);

bool	init_idle(t_data* game);

bool	init_walk(t_data* game);

bool	init_run(t_data* game);

bool	init_lookat(t_data* game);

bool	set_image_and_data(t_data *game, t_sprite_sheet *anim, \
	char *anim_identifier);

/***************************Fs_Map System************************************ */

void	init_fs_minimap_settings(t_data *game, t_int_vector *start, \
	t_int_vector *end);

void 	draw_fs_minimap(t_data *game);

void	draw_fs_minimap_player(t_data *game);

void	update_fs_minimap_camera_offset(t_data *game);

/***************************Minimap System*********************************** */

void	draw_minimap_player(t_data *game);

void	draw_entire_minimap(t_data *game);

void 	update_minimap_camera_offset(t_data *game);

void	init_minimap_settings(t_data *game, t_int_vector *start, \
	t_int_vector *end);

/***************************Anims******************************************** */

void	update_sprite_sheet(t_sprite_sheet *anim, float delta_time);

void	draw_sprite_sheet_anim(t_sprite_sheet *anim, t_img *screen);

void	select_animation(t_data *game, float delta_time);

/***************************Player moves and events************************** */

void 	update_player(t_data *game, float delta_time);

int		key_press(int keycode, void *param);

int		key_release(int keycode, void *param);

int 	mouse_handler(int x, int y, void *param);

int		focus_out_handler(t_data *game);

void 	rotate_vector(t_vector *v, float angle);

void	teleport_player_crossing_portal(t_data *game);

bool	did_cross_portal(t_player *player, t_portal *portal);

bool	hitboxes_checker(t_data *game, float x, float y);

bool	is_player_moving(t_key_state *key_state);

void	teleport_to_portal(t_portal *in, t_portal *out, t_player *player);

/*******************************Game States********************************** */

void	game_states_mswitch(t_data *game);

void	select_map(t_data *game);

/*******************************Portals************************************** */

void	create_portal(t_ray *ray, t_portal *portal);

bool	check_for_portal(t_portal *portal, t_ray *ray);

void	define_portal_segment(t_portal *portal);

bool	player_hb_intersects_with_segment(t_vector *pos, t_portal *portal);

void	draw_portal_slice(int win_x, t_data *game, t_ray *ray);

bool	is_point_on_segment(t_vector point, t_vector seg_strt, t_vector seg_end);

float	compute_rotation_angle(t_vector *v1, t_vector *v2);

void	facing_to_vector(t_facing face, t_vector *vector);

void	init_ray_step_and_dist(t_player *player, t_ray *ray);

void	portal_builder(t_data *game, t_ray *ray, int x);

/*******************************Raycast/DDA********************************** */

int 	game_loop(void * param);

float	get_delta_time(void);

void 	img_pixel_put(int x, int y, int color, t_img *img);

t_ray	init_ray(t_player *player, int x);

void	cast_ray(char **map_grid, t_ray *ray);

void	draw_ceiling_and_floor(t_img *img, int ceiling_color, int floor_color);

double	compute_projected_wall_dist(t_ray *ray, bool wall_tile_hit_side);

void	draw_ceiling_and_floor(t_img *img, int ceiling_color, int floor_color);

void	draw_crosshair(t_data *game);

t_draw	compute_draw_limits(double proj_wall_hit_dist);

t_texture	get_wall_tex(t_ray *ray, t_data *game, \
	double *wall_hit_x);

/*****************************Texture Mapping******************************** */

t_draw	compute_draw_limits(double proj_wall_hit_dist);

void	draw_wall_slice(int win_x, t_data *game, t_ray *ray);

void	img_pixel_put(int x, int y, int color, t_img *img);

bool	check_flip_textures(t_ray *ray);

int		get_texture_color(int tex_x, int tex_y, t_texture *wall);

int		compute_texture_y(int pixel_y, int wall_slice_height, int tex_height);

int		compute_texture_x(double wall_hit_x, t_ray *ray, int tex_width);

/*******************************Vectors Maths******************************** */

t_vector 	add_vectors(t_vector v1, t_vector v2);

t_vector 	substract_vectors(t_vector v1, t_vector v2);

float 		vector_length(t_vector v);

t_vector 	scalar_mult(t_vector v, float scalar);

t_vector 	normalize_vector(t_vector v);

float 		dot_product(t_vector v1, t_vector v2);

t_vector 	get_direction_from_angle(float angle);

float		dot_product(t_vector v1, t_vector v2);

void		rotate_dvector(t_double_vector *v, float angle);

#endif