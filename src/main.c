#include <stdio.h>
#include "cub3D.h"
#include "parsing.h"
#include "raycast.h"
#include "mlx.h"
#include <math.h>

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720
#define TILE_SIZE 64
#define FOV (M_PI / 3)

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct s_player
{
	t_vector pos;
	float angle;
}	t_player;

// int	main(int argc, char **argv)
// {

// 	(void)argc;
// 	(void)argv;
// 	if (parsing(argc, argv) == 0)
// 	{
// 		printf("Parsing failed\n");
// 		return (1);
// 	}
// 	return (0);
// }

float normalize_angle(float angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

float cast_ray(t_player player, float ray_angle)
{	
	ray_angle = normalize_angle(ray_angle);

	int	map_x = (int)(player.pos.x / TILE_SIZE);
	int	map_y = (int)(player.pos.y / TILE_SIZE);

	float ray_dir_x = cosf(ray_angle);
	float ray_dir_y = sinf(ray_angle);

	float delta_dist_x;
	float delta_dist_y;

	if (ray_dir_x == 0)
		delta_dist_x = 1e30;
	else
		delta_dist_x = fabsf(1 / ray_dir_x);
	if (ray_dir_y == 0)
		delta_dist_y = 1e30;
	else
		delta_dist_y = fabsf(1 / ray_dir_y);

	int step_x, step_y;
	float side_dist_x, side_dist_y;

	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (player.pos.x - map_x * TILE_SIZE) * delta_dist_x / TILE_SIZE;
	}
	else
	{
		step_x = 1;
		side_dist_x = ((map_x + 1) * TILE_SIZE - player.pos.x) * delta_dist_x * TILE_SIZE;
	}

}


int main(void)
{
	void *mlx;
	void *win;
	t_player player;
	
	int map[3][3] = 
	{
		{1,1,1},
		{1,0,1},
		{1,1,1}
	};

	player.pos.x = (1.5) * TILE_SIZE;
	player.pos.y = (1.5) * TILE_SIZE;
	player.angle = 0;

	mlx = mlx_init();
	win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, "RAYCASTUUUUUUUUUU");


	mlx_loop(mlx);
	return (0);
}