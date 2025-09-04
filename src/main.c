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

char hc_map[MAP_HEIGHT][MAP_WIDTH + 1] = {
		"11111111111111111111111111111",
		"10000000001100000000000000001",
		"10110000011100000000000000001",
		"10010000000000000000000000001",
		"11111111101100000111000000001",
		"10000000001100000111000001111",
		"11110111111111011100000010001",
		"11110111111111011101010010001",
		"11000000110101011100000010001",
		"1000000P000000001100000010001",
		"10000000000000001101010010001",
		"11000001110101011111011110111",
		"11110111111101011101111010001",
		"11111111111111111111111111111",};

void find_player_pos(t_player *player, char **map)
{
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			if (map[y][x] == 'P')
			{
				player->pos.x = (float)x + 0.5;
				player->pos.y = (float)y + 0.5;
				map[y][x] = '0';
			}
		}
	}
}

char **create_map(void)
{
	char **map;
	int	i;

	i = 0;
	map = malloc((MAP_HEIGHT + 1) * sizeof(char *));
	while (i < MAP_HEIGHT)
	{
		map[i] = ft_strdup(hc_map[i]);
		i++;
	}
	map[i] = NULL;
	return (map);
}

bool	init_textures_data(t_data *game)
{
	game->n_wall.data = mlx_get_data_addr(game->n_wall.texture,\
		&game->n_wall.bpp, &game->n_wall.size_line, &game->n_wall.endian);
	if (!game->n_wall.data)
		return (false);
	game->w_wall.data = mlx_get_data_addr(game->w_wall.texture,\
		&game->w_wall.bpp, &game->w_wall.size_line, &game->w_wall.endian);
	if (!game->w_wall.data)
		return (false);
	game->e_wall.data = mlx_get_data_addr(game->e_wall.texture,\
		&game->e_wall.bpp, &game->e_wall.size_line, &game->e_wall.endian);
	if (!game->e_wall.data)
		return (false);
	game->s_wall.data = mlx_get_data_addr(game->s_wall.texture,\
		&game->s_wall.bpp, &game->s_wall.size_line, &game->s_wall.endian);
	if (!game->s_wall.data)
		return (false);
	return (true);
}

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

void	init_player(t_data *game, t_player *player)
{
	player->angle = M_PI / 2;
	player->dir = get_direction_from_angle(player->angle);
	player->plane.x = -player->dir.y * tan(FOV / 2);
	player->plane.y = player->dir.x * tan(FOV / 2);
	find_player_pos(player, game->map);
	game->player = player;
}

bool	init_mlx_and_textures(t_data *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (false);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, \
		"RAYCASTUUUUU");
	if (!game->win)
		return (false);
	game->img_ptr = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img_ptr)
		return (false);
	game->img_data = mlx_get_data_addr(game->img_ptr, &game->bpp, \
		&game->size_line, &game->endian);
	if (!game->img_data)
		return (false);
	if (!init_textures(game))
		return (false);
	game->display = XOpenDisplay(NULL);
	game->main_win = DefaultRootWindow(game->display);
	mlx_hook(game->win, KeyPress, KeyPressMask, key_press, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, key_release, \
		game->key_state);
	mlx_hook(game->win, MotionNotify, PointerMotionMask, mouse_handler, game); // BONUS : mouse_handling
	mlx_hook(game->win, FocusOut, FocusChangeMask, focus_out_handler, game);
	mlx_hook(game->win, DestroyNotify, NoEventMask, exit_game, game);
	return (true);
}

int main(int argc, char **argv)
{
	t_context ctx;
	int fd;

	check_arguments(argc, argv);
	ctx_init(&ctx);
	config_init(&ctx.conf);
	map_init(&ctx.map);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	if (parse_cube(fd, &ctx) == 0)
	{
		context_free(&ctx);
		config_free(&ctx.conf);
		printf("Parsing failed\n");
		return (1);
	}
	context_free(&ctx);
	config_free(&ctx.conf);
	t_data 		game;
	t_player	player;
	t_key_state	key_state = {0};

	ft_memset(&game, 0, sizeof(t_data));
	game.key_state = &key_state;
	game.mouse_activated = false;
	game.fs_map = false;
	game.map = create_map();
	game.minimap_cam.x = 0;
	game.minimap_cam.y = 0;
	init_player(&game, &player);
	init_mlx_and_textures(&game);
	mlx_loop_hook(game.mlx, &raycast_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
