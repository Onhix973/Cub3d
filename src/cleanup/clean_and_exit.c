#include "structs.h"
#include "cub3D.h"
#include "mlx.h"
#include <stdlib.h>

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	if (tab && !*tab)
	{
		free(tab);
		return ;
	}
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return ;
}

void	destroy_textures(t_data *game)
{
	mlx_destroy_image(game->mlx, game->n_wall.texture);
	mlx_destroy_image(game->mlx, game->e_wall.texture);
	mlx_destroy_image(game->mlx, game->w_wall.texture);
	mlx_destroy_image(game->mlx, game->s_wall.texture);
	mlx_destroy_image(game->mlx, game->img_ptr);
}

int	exit_game(void *param)
{
	t_data	*game;

	game = (t_data *)param;
	destroy_textures(game);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	XCloseDisplay(game->display);
	free(game->mlx);
	free_tab(game->map);
	exit(0);
}
