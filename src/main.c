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
	t_sprite_sheet	anim;
	int	frame_w;
	int	frame_h;

	ft_memset(&game, 0, sizeof(t_data));
	context_creator(argc, argv, &ctx);
	game.ctx = &ctx;
	game.key_state = &key_state;
	game.mouse_activated = false;
	game.fs_map = false;
	game.map = ctx.map.grid;
	game.map_width = ctx.map.width;
	game.map_height = ctx.map.height;
	game.minimap_width = WIN_WIDTH / 6.4;
	game.minimap_height = WIN_HEIGHT / 3.6;
	game.minimap_margin = game.minimap_width / 10;
	compute_fs_map_size(&game);
	init_player(&game, &player);
	init_mlx_and_textures(&game);
	game.background.ptr = mlx_new_image(game.mlx, WIN_WIDTH, WIN_HEIGHT);
	game.background.data = mlx_get_data_addr(game.background.ptr, \
		&game.background.bpp, &game.background.size_line, &game.background.endian);
	draw_ceiling_and_floor(&game.background, \
		game.ctx->conf.ceil_hex, game.ctx->conf.floor_hex);

	//TODO Don't forget to free and make this cleaner
	anim.sheet.ptr = mlx_xpm_file_to_image(game.mlx, "textures/Walk.xpm", &frame_w, &frame_h);
	anim.sheet.data = mlx_get_data_addr(anim.sheet.ptr, &anim.sheet.bpp, &anim.sheet.size_line, &anim.sheet.bpp);
	anim.frame_h = 128;
	anim.frame_w = 128;
	anim.num_frames = 10;
	anim.frames_per_row = 10;
	anim.curr_frame = 0;
	anim.elapsed_time = 0;
	anim.frame_time = 0.1;
	anim.x = 500;
	anim.y = 500;
	game.anim = &anim;
	//TODO
	
	mlx_loop_hook(game.mlx, &raycast_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
