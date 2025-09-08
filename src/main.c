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

void	compute_player_angle(t_data *game)
{
	game->player->angle = 0.0f;
	if (game->ctx->map.player_dir == 'N')
		game->player->angle = M_PI / 2;
	if (game->ctx->map.player_dir == 'E')
		game->player->angle = 0;
	if (game->ctx->map.player_dir == 'S')
		game->player->angle = (3 * M_PI) / 2;
	if (game->ctx->map.player_dir == 'W')
		game->player->angle = M_PI;
}

void	init_player(t_data *game, t_player *player)
{
	game->player = player;
	compute_player_angle(game);
	player->dir = get_direction_from_angle(player->angle);
	player->plane.x = -player->dir.y * tan(FOV / 2);
	player->plane.y = player->dir.x * tan(FOV / 2);
	player->pos.x = (float)game->ctx->map.player_x + 0.5;
	player->pos.y = (float)game->ctx->map.player_y + 0.5;
}

bool	init_mlx_and_textures(t_data *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (false);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, \
		"Cub3D");
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
	game.minimap_cam.x = 0;
	game.minimap_cam.y = 0;
	game.map_width = ctx.map.width;
	game.map_height = ctx.map.height;
	if (game.map_width * FS_MAP_SCALE < WIN_WIDTH)
		game.fs_map_width = game.map_width * FS_MAP_SCALE;
	else
		game.fs_map_width = WIN_WIDTH - 32;
	if (game.map_width * FS_MAP_SCALE < WIN_HEIGHT)
		game.fs_map_height = game.map_height * FS_MAP_SCALE;
	else
		game.fs_map_height = WIN_HEIGHT - 32;
	game.fs_map_height = game.map_height * FS_MAP_SCALE;
	game.fs_map_x = (WIN_WIDTH - game.fs_map_width) / 2;
	game.fs_map_y = (WIN_HEIGHT - game.fs_map_height) / 2;
	init_player(&game, &player);
	init_mlx_and_textures(&game);
	mlx_loop_hook(game.mlx, &raycast_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
