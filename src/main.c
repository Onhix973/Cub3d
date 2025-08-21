#include <stdio.h>
#include "cub3D.h"
#include "parsing.h"
#include "raycast.h"
#include "mlx.h"
#include "libft.h"
#include <X11/keysym.h>
#include <X11/X.h>
#include <math.h>

#define WIN_WIDTH 640
#define WIN_HEIGHT 480
#define MAP_WIDTH 26
#define MAP_HEIGHT 5
#define TILE_SIZE 64
#define FOV (M_PI / 3)
#define WALL_COLOR 0xAA00AA

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct s_player
{
	t_vector pos;
	t_vector dir;
	t_vector plane;
	float angle;
}	t_player;

char map[MAP_HEIGHT][MAP_WIDTH + 1] = {
    "1111111111111111111111111",
    "1000000000110000000000001",
    "1011000001110000000000001",
    "1001000P00000000000000001",
    "1111111111111111111111111",};

void *mlx_ptr;
void *win_ptr;
void *img_ptr;
char *img_data;
int bpp;
int size_line;
int endian;

void rotate_vector(t_vector *v, float angle)
{
	float oldx = v->x;
	v->x = v->x * cosf(angle) - v->y * sinf(angle);
	v->y = oldx * sinf(angle) + v->y * cosf(angle);
}

int key_press(int keycode, t_player *player)
{
	float rotation_speed = 0.05;
	float move_speed = 0.9;

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
	else if (keycode == XK_a)
	{
		rotate_vector(&player->dir, -rotation_speed);
		rotate_vector(&player->plane, -rotation_speed);
	}
	else if (keycode == XK_d)
	{
		rotate_vector(&player->dir, rotation_speed);
		rotate_vector(&player->plane, rotation_speed);
	}
	return (0);
}

void img_pixel_put(int x, int y, int color)
{
	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	char *pixel;
	pixel = img_data + (y * size_line) + (x * (bpp / 8));
	*(unsigned int *)pixel = color;
}

int raycast_loop(void * param)
{
	t_player *player = (t_player *)param;
	ft_memset(img_data, 0, WIN_HEIGHT * size_line);
	for (int x = 0; x < WIN_WIDTH; x++)
	{
		double camerax = 2 * x / (double)WIN_WIDTH - 1;
		double raydirx = player->dir.x + player->plane.x * camerax;
		double raydiry = player->dir.y + player->plane.y * camerax;

		int mapx = (int)player->pos.x;
		int mapy = (int)player->pos.y;

		double sidedistx;
		double sidedisty;

		double deltadistx = fabs(1 / raydirx);
		double deltadisty = fabs(1 / raydiry);

		int stepx, stepy;

		if (raydirx < 0)
		{
			stepx = -1;
			sidedistx = (player->pos.x - mapx) * deltadistx;
		}
		else
		{
			stepx = 1;
			sidedistx = (mapx + 1.0 - player->pos.x) * deltadistx;
		}
		if (raydiry < 0)
		{
			stepy = -1;
			sidedisty = (player->pos.y - mapy) * deltadisty;
		}
		else
		{
			stepy = 1;
			sidedisty = (mapy + 1.0 - player->pos.y) * deltadisty;
		}
		int	hit = 0;
		int side;
		
		while (!hit)
		{
			if (sidedistx < sidedisty)
			{
				sidedistx += deltadistx;
				mapx += stepx;
				side = 0;
			}
			else
			{
				sidedisty += deltadisty;
				mapy += stepy;
				side = 1;
			}
			if (map[mapy][mapx] == '1')
				hit = 1;
		}
		double perpwalldist = (side == 0) ? (sidedistx - deltadistx) : (sidedisty - deltadisty);
		int lineheight = (int)(WIN_HEIGHT / perpwalldist);
		int drawstart = -lineheight / 2 + WIN_HEIGHT / 2;
		if (drawstart < 0)
			drawstart = 0;
		int drawend = lineheight / 2 + WIN_HEIGHT / 2;
		if (drawend >= WIN_HEIGHT)
			drawend = WIN_HEIGHT - 1;
		for (int y = drawstart; y < drawend; y++)
			img_pixel_put(x, y , WALL_COLOR);
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
	return (0);
}

void find_player_pos(t_player *player)
{
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x< MAP_WIDTH; x++)
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

int mouse_handler(int x, int y, void *param)
{
	(void)y;
	static int last_x = -1;
	t_player *player = (t_player *)param;
	if (!player)
		return (0);
	float sens = 0.003f;

	if (last_x == -1)
		last_x = x;

	int delta_x = x - last_x;
	last_x = x;

	float angle = delta_x * sens;
	rotate_vector(&player->dir, angle);
	rotate_vector(&player->plane, angle);
	return (0);
}

int main(void)
{
	t_player player;

	player.angle = (3 * M_PI) / 2;
	
	player.dir = get_direction_from_angle(player.angle);
	player.plane.x = -player.dir.y * tan(FOV / 2);
	player.plane.y = player.dir.x * tan(FOV / 2);
	find_player_pos(&player);


	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "RAYCASTUUUUU");
	img_ptr = mlx_new_image(mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	img_data = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);

	mlx_hook(win_ptr, KeyPress, KeyPressMask, key_press, &player);
	mlx_hook(win_ptr, MotionNotify, PointerMotionMask, mouse_handler, &player);
	mlx_loop_hook(mlx_ptr, &raycast_loop, &player);
	mlx_loop(mlx_ptr);
	return (0);
}