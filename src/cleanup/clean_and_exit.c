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

void config_free(t_config *c)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (c->path[i] != NULL)
			free(c->path[i]);
		c->path[i] = NULL;
		i++;
	}
}

void context_free(t_context *ctx)
{
	map_free(&ctx->map);
	config_free(&ctx->conf);
	free_split(ctx->lines);
	ctx->lines = NULL;
}

void	destroy_textures(t_data *game)
{
	mlx_destroy_image(game->mlx, game->n_wall.texture);
	mlx_destroy_image(game->mlx, game->e_wall.texture);
	mlx_destroy_image(game->mlx, game->w_wall.texture);
	mlx_destroy_image(game->mlx, game->s_wall.texture);
	mlx_destroy_image(game->mlx, game->main_img.ptr);
	mlx_destroy_image(game->mlx, game->background.ptr);
	mlx_destroy_image(game->mlx, game->anims.idle.sheet.ptr);
	mlx_destroy_image(game->mlx, game->anims.run.sheet.ptr);
	mlx_destroy_image(game->mlx, game->anims.walk.sheet.ptr);
	mlx_destroy_image(game->mlx, game->anims.attack.sheet.ptr);
	mlx_destroy_image(game->mlx, game->anims.block.sheet.ptr);
	mlx_destroy_image(game->mlx, game->anims.lookat.sheet.ptr);
	mlx_destroy_image(game->mlx, game->portal.texture);
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
	// context_free(game->ctx);
	// config_free(&game->ctx->conf);
	exit(0);
}
