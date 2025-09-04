#include "structs.h"

bool	init_textures(t_data *game)
{
	game->n_wall.texture = mlx_xpm_file_to_image(game->mlx, N_WALL_TEXTURE,\
	&game->n_wall.width, &game->n_wall.height);
	if (!game->n_wall.texture)
		return (false);
	game->w_wall.texture = mlx_xpm_file_to_image(game->mlx, W_WALL_TEXTURE,\
	&game->w_wall.width, &game->w_wall.height);
	if (!game->w_wall.texture)
		return (false);
	game->e_wall.texture = mlx_xpm_file_to_image(game->mlx, E_WALL_TEXTURE,\
	&game->e_wall.width, &game->e_wall.height);
	if (!game->e_wall.texture)
		return (false);
	game->s_wall.texture = mlx_xpm_file_to_image(game->mlx, S_WALL_TEXTURE,\
	&game->s_wall.width, &game->s_wall.height);
	if (!game->s_wall.texture)
		return (false);
	if (!init_textures_data(game))
		return (false);
	return (true);
}
