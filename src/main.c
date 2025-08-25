#include <stdio.h>
#include "cub3D.h"
#include "parsing.h"
#include "raycast.h"
#include "mlx.h"
#include "libft.h"
#include <X11/keysym.h>
#include <X11/X.h>
#include <math.h>

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

void rotate_vector(t_vector *v, float angle)
{
	float oldx = v->x;
	v->x = v->x * cosf(angle) - v->y * sinf(angle);
	v->y = oldx * sinf(angle) + v->y * cosf(angle);
}

int key_press(int keycode, t_data *game)
{
	float rotation_speed = 0.25;
	float move_speed = 0.7;
	t_player *player = game->player;
	char **map = game->map;
	int map_x = (int)(player->pos.x);
	int map_y = (int)(player->pos.y);

	printf("Keycode: %d\n", keycode);
	if (keycode == XK_w)
	{
		if (map[map_y][(int)(player->pos.x + player->dir.x * move_speed)] == '0')
			player->pos.x += player->dir.x * move_speed;
		if (map[(int)(player->pos.y + player->dir.y * move_speed)][map_x] == '0')
			player->pos.y +=player->dir.y * move_speed;
	}
	else if (keycode == XK_s)
	{
		if (map[map_y][(int)(player->pos.x - player->dir.x * move_speed)] == '0')
			player->pos.x -= player->dir.x * move_speed;
		if (map[(int)(player->pos.y - player->dir.y * move_speed)][map_x] == '0')
			player->pos.y -=player->dir.y * move_speed;
	}
	else if (keycode == XK_d)
	{
		if (map[map_y][(int)(player->pos.x + (-player->dir.y) * move_speed)] == '0')
			player->pos.x += (-player->dir.y) * move_speed;
		if (map[(int)(player->pos.y + player->dir.x * move_speed)][map_x] == '0')
			player->pos.y += player->dir.x * move_speed;
	}
	else if (keycode == XK_a)
	{
		if (map[map_y][(int)(player->pos.x + (player->dir.y) * move_speed)] == '0')
			player->pos.x += (player->dir.y) * move_speed;
		if (map[(int)(player->pos.y + -player->dir.x * move_speed)][map_x] == '0')
			player->pos.y += -player->dir.x * move_speed;
	}
	else if (keycode == XK_Left)
	{
		rotate_vector(&player->dir, -rotation_speed);
		rotate_vector(&player->plane, -rotation_speed);
	}
	else if (keycode == XK_Right)
	{
		rotate_vector(&player->dir, rotation_speed);
		rotate_vector(&player->plane, rotation_speed);
	}
	return (0);
}

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

#include <X11/X.h>

// int mouse_handler(int x, int y, void *param)
// {
// 	(void)y;
// 	static int last_x = -1;
// 	t_player *player = (t_player *)param;
// 	if (!player)
// 		return (0);
// 	float sens = 0.003f;

// 	if (last_x == -1)
// 		last_x = x;

// 	int delta_x = x - last_x;
// 	last_x = x;

// 	float angle = delta_x * sens;
// 	rotate_vector(&player->dir, angle);
// 	rotate_vector(&player->plane, angle);

// 	return (0);
// }

int main(void)
{
	t_data game;
	
	t_player player;
	game.map = create_map();
	player.angle = (3 * M_PI) / 2;
	player.dir = get_direction_from_angle(player.angle);
	player.plane.x = -player.dir.y * tan(FOV / 2);
	player.plane.y = player.dir.x * tan(FOV / 2);
	find_player_pos(&player, game.map);

	game.player = &player;
	game.mlx_ptr = mlx_init();
	game.win_ptr = mlx_new_window(game.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "RAYCASTUUUUU");
	game.img_ptr = mlx_new_image(game.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	game.img_data = mlx_get_data_addr(game.img_ptr, &game.bpp, &game.size_line, &game.endian);

	mlx_hook(game.win_ptr, KeyPress, KeyPressMask, key_press, &game);
	// mlx_hook(win_ptr, MotionNotify, PointerMotionMask, mouse_handler, &player); // BONUS : mouse_handling
	mlx_loop_hook(game.mlx_ptr, &raycast_loop, &game);
	mlx_loop(game.mlx_ptr);
	free_tab(game.map);
	return (0);
}
