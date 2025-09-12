#ifndef STRUCTS_H
# define STRUCTS_H

#include "parsing.h"
#include <stdbool.h>
#include <X11/extensions/Xfixes.h>

#define NB_OF_MAP_PARAMS 6

typedef struct s_key_state	t_key_state;
typedef struct s_portal		t_portal;

typedef enum r_cardinals
{
	NO, SO, WE, EA, FLOOR, CEIL
} 	t_cardinals;

typedef struct s_config
{
	int seen[NB_OF_MAP_PARAMS];
	char *path[4];
	int floor[3];
	int ceil[3];
	int floor_hex;
	int ceil_hex;
	int	i_map_start;
}	t_config;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	char	player_dir;
} 	t_map;

typedef struct s_context
{
	t_config conf;
	t_map	map;
	char	**lines;
} 	t_context;

typedef struct s_vector
{
	float x;
	float y;
}	t_vector;

typedef struct s_int_vector
{
	int	x;
	int	y;
}	t_int_vector;

typedef struct s_player
{
	t_vector 	pos;
	t_vector 	dir;
	t_vector 	camera_plane;
	float 		angle;
}	t_player;

typedef struct s_texture
{
	void	*texture;
	char	*data;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_texture;

typedef struct s_img
{
	void	*ptr;
	void	*data;
	int		bpp;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_data
{
	void 			*mlx;
	void 			*win;
	t_img			main_img;
	t_img			background;
	bool			mouse_activated;
	bool			fs_map;
	t_player 		*player;
	char			**map;
	t_key_state		*key_state;
	t_texture		n_wall;
	t_texture		w_wall;
	t_texture		e_wall;
	t_texture		s_wall;
	Window			main_win;
	Display			*display;
	t_context		*ctx;
	int				map_width;
	int				map_height;
	int				fs_map_height;
	int				fs_map_width;
	int				fs_map_x;
	int				fs_map_y;
	t_int_vector	minimap_cam;
}	t_data;

typedef struct s_ray
{
	double		win_x_pos;
	double		dir_x;
	double		dir_y;
	t_int_vector	map_tile;
	t_int_vector	tile_step;
	double		dist_next_hgrid;
	double		dist_next_vgrid;
	double		delta_dist_x;
	double		delta_dist_y;
	double		cos_view_angle;
}	t_ray;

typedef struct s_hit
{
	int		wall_tile_hit_side;
	double	proj_wall_hit_dist;
}	t_hit;

typedef struct s_draw
{
	int	line_height;
	int	draw_start;
	int	draw_end;
}	t_draw;

typedef struct s_key_state
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	left;
	bool	right;
	bool	shift;
	bool	c;
	bool	v;
	bool	tab;
}	t_key_state;

// typedef struct s_portal
// {
// 	int				x;
// 	int				y;
// 	struct s_portal	linked_portal;
// }	t_portal;

#endif