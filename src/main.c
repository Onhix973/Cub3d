#include <stdio.h>
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

char **create_map(void)
{
	char **map;
	int	i;

	i = 0;
	map = malloc(MAP_HEIGHT * sizeof(char *));
	while (i < MAP_HEIGHT)
	{
		map[i] = ft_strdup(hc_map[i]);
		i++;
	}
	return (map);
}

void	init_textures(t_data *game)
{
	game->n_wall.texture = mlx_xpm_file_to_image(game->mlx_ptr, N_WALL_TEXTURE,\
	&game->n_wall.width, &game->n_wall.height);
	game->n_wall.data = mlx_get_data_addr(game->n_wall.texture,\
		&game->n_wall.bpp, &game->n_wall.size_line, &game->n_wall.endian);

	game->w_wall.texture = mlx_xpm_file_to_image(game->mlx_ptr, W_WALL_TEXTURE,\
	&game->w_wall.width, &game->w_wall.height);
	game->w_wall.data = mlx_get_data_addr(game->w_wall.texture,\
		&game->w_wall.bpp, &game->w_wall.size_line, &game->w_wall.endian);

	game->e_wall.texture = mlx_xpm_file_to_image(game->mlx_ptr, E_WALL_TEXTURE,\
	&game->e_wall.width, &game->e_wall.height);
	game->e_wall.data = mlx_get_data_addr(game->e_wall.texture,\
		&game->e_wall.bpp, &game->e_wall.size_line, &game->e_wall.endian);

	game->s_wall.texture = mlx_xpm_file_to_image(game->mlx_ptr, S_WALL_TEXTURE,\
	&game->s_wall.width, &game->s_wall.height);
	game->s_wall.data = mlx_get_data_addr(game->s_wall.texture,\
		&game->s_wall.bpp, &game->s_wall.size_line, &game->s_wall.endian);
}
void free_tab_tab(char **tab)
{
	int i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int main(int argc, char **argv)
{
	t_data game;
	t_player player;
	t_key_state	key_state = {0};
	t_config config;

	if (parsing(argc, argv) == 0)
	{
		printf("Parsing failed\n");
		return (1);
	}
	game.key_state = &key_state;
	game.mouse_activated = false;
	game.map = create_map();
	player.angle = M_PI / 2;
	player.dir = get_direction_from_angle(player.angle);
	player.plane.x = -player.dir.y * tan(FOV / 2);
	player.plane.y = player.dir.x * tan(FOV / 2);
	find_player_pos(&player, game.map);
	game.player = &player;
	game.mlx_ptr = mlx_init();
	game.win_ptr = mlx_new_window(game.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "RAYCASTUUUUU");
	game.img_ptr = mlx_new_image(game.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	game.img_data = mlx_get_data_addr(game.img_ptr, &game.bpp, &game.size_line, &game.endian);
	init_textures(&game);
	game.display = XOpenDisplay(NULL);
	game.main_win = DefaultRootWindow(game.display);
	mlx_hook(game.win_ptr, KeyPress, KeyPressMask, key_press, game.key_state);
	mlx_hook(game.win_ptr, KeyRelease, KeyReleaseMask, key_release, game.key_state);
	mlx_hook(game.win_ptr, MotionNotify, PointerMotionMask, mouse_handler, &game); // BONUS : mouse_handling
	mlx_hook(game.win_ptr, FocusOut, FocusChangeMask, focus_out_handler, &game);
	mlx_loop_hook(game.mlx_ptr, &raycast_loop, &game);
	mlx_loop(game.mlx_ptr);
	free_tab_tab(config->map);
	// mlx_destroy_image(game.mlx_ptr, game.wall.texture);
	// mlx_destroy_window(game.mlx_ptr, game.win_ptr);
	// mlx_destroy_display(game.mlx_ptr);
	// free_tab(game.map);
	return (0);
}
