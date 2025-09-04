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

int parse_map_block(t_context *ctx)
{
	char **map_lines;

	map_lines = NULL;
	if (extract_map_only(ctx->lines, &ctx->conf, &map_lines) != 1)
		return (0);
	if (valid_map_syntax(map_lines, ctx) != 1)
	{
		free_split(map_lines);
		return (0);
	}
	if (rect_map(map_lines, &ctx->map) != 1)
	{
		free_split(map_lines);
		return (0);
	}
	free_split(map_lines);
	if (check_close(&ctx->map) != 1)
		return (0);
	return (1);
}

int parse_cube(int fd, t_context *ctx)
{
	if (load_lines(fd, &ctx->lines) != 1)
		return (0);
	if (parse_header(ctx->lines, &ctx->conf) != 1)
	{
		printf("Header parsing failed\n");
		return (0);
	}
	if (parse_map_block(ctx) != 1)
		return (0);
	return (1);
}

void	context_creator(int argc, char **argv, t_context *ctx)
{
	int	fd;

	check_arguments(argc, argv);
	ctx_init(ctx);
	config_init(&ctx->conf);
	map_init(&ctx->map);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		exit (1);
	}
	if (parse_cube(fd, ctx) == 0)
	{
		context_free(ctx);
		config_free(&ctx->conf);
		printf("Parsing failed\n");
		exit (1);
	}
}

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
