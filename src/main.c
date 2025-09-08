#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include "cub3D.h"
#include "parsing.h"
#include "raycast.h"
#include "mlx.h"
#include "libft.h"
#include <X11/keysym.h>
#include <X11/X.h>
#include <math.h>
#include <sys/time.h>
#include <X11/extensions/Xfixes.h>

void	compute_fs_map_size(t_data *game)
{
	if (game->map_width * FS_MAP_SCALE < WIN_WIDTH)
		game->fs_map_width = game->map_width * FS_MAP_SCALE;
	else
		game->fs_map_width = WIN_WIDTH - 64;
	if (game->map_height * FS_MAP_SCALE < WIN_HEIGHT)
		game->fs_map_height = game->map_height * FS_MAP_SCALE;
	else
		game->fs_map_height = WIN_HEIGHT - 64;
	game->fs_map_x = (WIN_WIDTH - game->fs_map_width) / 2;
	game->fs_map_y = (WIN_HEIGHT - game->fs_map_height) / 2;
}

int main(int argc, char **argv)
{
	t_context 	ctx;
	t_data 		game;
	t_player	player;
	t_key_state	key_state = {0};

	ft_memset(&game, 0, sizeof(t_data));
	context_creator(argc, argv, &ctx);
	game.ctx = &ctx;
	game.key_state = &key_state;
	game.mouse_activated = false;
	game.fs_map = false;
	game.map = ctx.map.grid;
	game.map_width = ctx.map.width;
	game.map_height = ctx.map.height;
	compute_fs_map_size(&game);
	init_player(&game, &player);
	init_mlx_and_textures(&game);
	mlx_loop_hook(game.mlx, &raycast_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
