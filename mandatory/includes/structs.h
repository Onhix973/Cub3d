/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:40:40 by tlutz             #+#    #+#             */
/*   Updated: 2025/11/28 16:08:16 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>
# include <X11/extensions/Xfixes.h>
# include <sys/time.h>

# define NB_OF_MAP_PARAMS 6

typedef struct s_key_state		t_key_state;
typedef struct s_portal			t_portal;
typedef struct s_portal_pair	t_portal_pair;

typedef enum r_cardinals
{
	NO,
	SO,
	WE,
	EA,
	FLOOR,
	CEIL
}	t_cardinals;

typedef struct s_config
{
	int		seen[NB_OF_MAP_PARAMS];
	char	*path[4];
	int		floor[3];
	int		ceil[3];
	int		floor_hex;
	int		ceil_hex;
	int		i_map_start;
}	t_config;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_map;

typedef struct s_context
{
	t_config	conf;
	t_map		map;
	char		**lines;
}	t_context;

typedef struct s_vector
{
	float	x;
	float	y;
}	t_vector;

typedef struct s_int_vector
{
	int	x;
	int	y;
}	t_int_vector;

typedef struct s_double_vector
{
	double	x;
	double	y;
}	t_double_vector;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	prev_pos;
	t_vector	camera_plane;
	float		angle;
}	t_player;

typedef struct s_tex
{
	void	*texture;
	char	*data;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_tex;

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
	void			*mlx;
	void			*win;
	t_img			main_img;
	t_img			background;
	t_player		*player;
	char			**map;
	int				map_width;
	int				map_height;
	t_key_state		*key_state;
	t_tex			n_wall;
	t_tex			w_wall;
	t_tex			e_wall;
	t_tex			s_wall;
}	t_data;

typedef struct s_ray
{
	double			win_x_pos;
	t_double_vector	dir;
	t_double_vector	delta_dist;
	t_int_vector	map_tile;
	t_int_vector	tile_step;
	double			dist_next_hgrid;
	double			dist_next_vgrid;
	int				wall_tile_hit_side;
	double			proj_wall_hit_dist;
}	t_ray;

typedef struct s_draw
{
	int	line_height;
	int	draw_start;
	int	draw_end;
}	t_draw;

typedef struct s_key_state
{
	bool			w;
	bool			a;
	bool			s;
	bool			d;
	bool			left;
	bool			right;
	bool			shift;
}	t_key_state;

#endif