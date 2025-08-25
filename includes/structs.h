#ifndef STRUCTS_H
# define STRUCTS_H

#include <stdbool.h>

typedef struct s_key_state	t_key_state;

typedef struct s_vector
{
	float x;
	float y;
}	t_vector;

typedef struct s_player
{
	t_vector pos;
	t_vector dir;
	t_vector plane;
	float angle;
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

typedef struct s_data
{
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
	char *img_data;
	int bpp;
	int size_line;
	int endian;
	t_player *player;
	char **map;
	t_key_state	*key_state;
	t_texture	wall;
}	t_data;

typedef struct s_ray
{
	double	camerax;
	double	dirx;
	double	diry;
	double	deltadistx;
	double	deltadisty;
	double	sidedistx;
	double	sidedisty;
	int		mapx;
	int		mapy;
	int		stepx;
	int		stepy;
}	t_ray;

typedef struct s_hit
{
	int		side;
	int		mapx;
	int		mapy;
	double	perpwalldist;
}	t_hit;

typedef struct s_draw
{
	int	lineheight;
	int	drawstart;
	int	drawend;
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
}	t_key_state;

#endif