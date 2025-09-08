#include "parsing.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int	parse_map_block(t_context *ctx)
{
	char	**map_lines;

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

void	update_context(t_context *ctx)
{
	rgb_to_hex(ctx->conf.floor, &ctx->conf.floor_hex);
	rgb_to_hex(ctx->conf.ceil, &ctx->conf.ceil_hex);
}

int	parse_cube(int fd, t_context *ctx)
{
	if (load_lines(fd, &ctx->lines) != 1)
		return (0);
	if (parse_header(ctx->lines, &ctx->conf) != 1)
		return (0);
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
		perror("Error:\nerror opening file");
		exit (1);
	}
	if (parse_cube(fd, ctx) == 0)
	{
		context_free(ctx);
		config_free(&ctx->conf);
		exit (1);
	}
	update_context(ctx);
	close(fd);
}
