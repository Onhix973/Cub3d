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

float	get_delta_time(void)
{
	static struct timeval last_time = {0, 0};
	struct timeval current_time;
	float	delta = 0.0f;

	gettimeofday(&current_time, NULL);
	if (last_time.tv_sec != 0 || last_time.tv_usec != 0)
	{
		delta = (current_time.tv_sec - last_time.tv_sec) \
		+ (current_time.tv_usec - last_time.tv_usec) / 1000000.0f;
	}
	last_time = current_time;
	return (delta);
}

int	key_press(int keycode, void *param)
{
	t_key_state	*key_state;

	key_state = (t_key_state *)param;
	if (keycode == XK_w)
		key_state->w = true;
	else if (keycode == XK_a)
		key_state->a = true;
	else if (keycode == XK_s)
		key_state->s = true;
	else if (keycode == XK_d)
		key_state->d = true;
	else if (keycode == XK_Left)
		key_state->left = true;
	else if (keycode == XK_Right)
		key_state->right = true;
	return (0);
}

int	key_release(int keycode, void *param)
{
	t_key_state	*key_state;

	key_state = (t_key_state *)param;
	if (keycode == XK_w)
		key_state->w = false;
	else if (keycode == XK_a)
		key_state->a = false;
	else if (keycode == XK_s)
		key_state->s = false;
	else if (keycode == XK_d)
		key_state->d = false;
	else if (keycode == XK_Left)
		key_state->left = false;
	else if (keycode == XK_Right)
		key_state->right = false;
	return (0);
}

int update_player(t_data *game, float delta_time, t_key_state *key_state)
{
	float rotation_speed = 1.5f;
	float move_speed = 1.5f;
	t_player *player = game->player;
	char **map = game->map;
	int map_x = (int)(player->pos.x);
	int map_y = (int)(player->pos.y);
	float	new_x;
	float	new_y;

	if (key_state->w)
	{
		new_x = player->pos.x + player->dir.x * move_speed * delta_time;
		new_y = player->pos.y + player->dir.y * move_speed * delta_time;
		if (map[map_y][(int)new_x] == '0')
			player->pos.x = new_x;
		if (map[(int)new_y][map_x] == '0')
			player->pos.y = new_y;
	}
	else if (key_state->s)
	{
		new_x = player->pos.x - player->dir.x * move_speed * delta_time;
		new_y = player->pos.y - player->dir.y * move_speed * delta_time;
		if (map[map_y][(int)new_x] == '0')
			player->pos.x = new_x;
		if (map[(int)new_y][map_x] == '0')
			player->pos.y = new_y;
	}
	else if (key_state->d)
	{
		new_x = player->pos.x + (-player->dir.y) * move_speed * delta_time;
		new_y = player->pos.y + player->dir.x * move_speed * delta_time;
		if (map[map_y][(int)new_x] == '0')
			player->pos.x = new_x;
		if (map[(int)new_y][map_x] == '0')
			player->pos.y = new_y;
	}
	else if (key_state->a)
	{
		new_x = player->pos.x + (player->dir.y) * move_speed * delta_time;
		new_y = player->pos.y + (-player->dir.x) * move_speed * delta_time;
		if (map[map_y][(int)new_x] == '0')
			player->pos.x = new_x;
		if (map[(int)new_y][map_x] == '0')
			player->pos.y = new_y;
	}
	else if (key_state->left)
	{
		rotate_vector(&player->dir, -rotation_speed * delta_time);
		rotate_vector(&player->plane, -rotation_speed * delta_time);
	}
	else if (key_state->right)
	{
		rotate_vector(&player->dir, rotation_speed * delta_time);
		rotate_vector(&player->plane, rotation_speed * delta_time);
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
	t_key_state	key_state = {0};

	game.key_state = &key_state;
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
	game.wall.texture = mlx_xpm_file_to_image(game.mlx_ptr, "textures/wall.xpm",\
	&game.wall.width, &game.wall.height);
	
	game.wall.data = mlx_get_data_addr(game.wall.texture,\
		&game.wall.bpp, &game.wall.size_line, &game.wall.endian);
	mlx_hook(game.win_ptr, KeyPress, KeyPressMask, key_press, game.key_state);
	mlx_hook(game.win_ptr, KeyRelease, KeyReleaseMask, key_release, game.key_state);
	// mlx_hook(win_ptr, MotionNotify, PointerMotionMask, mouse_handler, &player); // BONUS : mouse_handling
	mlx_loop_hook(game.mlx_ptr, &raycast_loop, &game);
	mlx_loop(game.mlx_ptr);
	return (0);
}
