#include "structs.h"
#include "cub3D.h"
#include "raycast.h"
#include "mlx.h"
#include <stdlib.h>

void	img_annihilator(void *mlx, void *img)
{
	if (!img)
		return ;
	mlx_destroy_image(mlx, img);
}

void	destroy_textures(t_data *game)
{
	img_annihilator(game->mlx, game->n_wall.texture);
	img_annihilator(game->mlx, game->e_wall.texture);
	img_annihilator(game->mlx, game->w_wall.texture);
	img_annihilator(game->mlx, game->s_wall.texture);
	img_annihilator(game->mlx, game->main_img.ptr);
	img_annihilator(game->mlx, game->background.ptr);
	img_annihilator(game->mlx, game->anims.idle.sheet.ptr);
	img_annihilator(game->mlx, game->anims.run.sheet.ptr);
	img_annihilator(game->mlx, game->anims.walk.sheet.ptr);
	img_annihilator(game->mlx, game->anims.attack.sheet.ptr);
	img_annihilator(game->mlx, game->anims.block.sheet.ptr);
	img_annihilator(game->mlx, game->anims.lookat.sheet.ptr);
	img_annihilator(game->mlx, game->anims.afk.sheet.ptr);
	img_annihilator(game->mlx, game->portal.texture);
}

void	exit_error(t_data *game)
{
	destroy_textures(game);
	if (game->mlx && game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (game->display)
		XCloseDisplay(game->display);
	if (game->map)
		free_tab(game->map);
	exit(EXIT_FAILURE);
}

int	exit_game(void *param)
{
	t_data	*game;

	game = (t_data *)param;
	destroy_textures(game);
	if (game->mlx && game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (game->display)
		XCloseDisplay(game->display);
	if (game->map)
		free_tab(game->map);
	exit(EXIT_SUCCESS);
}
