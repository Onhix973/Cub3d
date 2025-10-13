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

int	mouse_hook(int button, int x, int y, void *param)
{
	t_data *game = (t_data *)param;
	(void)x;
	(void)y;
	if (button == 1)
	{
		if (!game->attack_state && !game->block_state && !game->inspect)
			game->attack_state = true;
	}
	else if (button == 3)
	{
		if (!game->block_state && !game->attack_state && !game->inspect)
			game->block_state = true;
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_context 	ctx;
	t_data 		game;
	t_player	player;
	t_key_state	key_state = {0};
	t_sprite_sheet	anim;
	t_sprite_sheet	lookat;
	t_sprite_sheet	idle;
	t_sprite_sheet	run;
	t_sprite_sheet	attack;
	t_sprite_sheet	block;
	t_portal		first_p = {0};
	int	frame_w;
	int	frame_h;

	ft_memset(&game, 0, sizeof(t_data));
	context_creator(argc, argv, &ctx);
	game.ctx = &ctx;
	game.key_state = &key_state;
	game.mouse_activated = false;
	game.fs_map = false;
	game.attack_state = false;
	game.inspect = false;
	game.block_state = false;
	game.first_p = &first_p;
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
	anim.sheet.ptr = mlx_xpm_file_to_image(game.mlx, "textures/spritesheet_walk.xpm", &frame_w, &frame_h);
	anim.sheet.data = mlx_get_data_addr(anim.sheet.ptr, &anim.sheet.bpp, &anim.sheet.size_line, &anim.sheet.bpp);
	anim.frame_w = 1280;
	anim.frame_h = 400;
	anim.num_frames = 10;
	anim.frames_per_row = 10;
	anim.curr_frame = 0;
	anim.elapsed_time = 0;
	anim.frame_time = 0.1f;
	anim.x = 0;
	anim.y = 320;
	game.anim = &anim;
	//TODO

	//TODO
	lookat.sheet.ptr = mlx_xpm_file_to_image(game.mlx, "textures/lookat.xpm", &frame_w, &frame_h);
	lookat.sheet.data = mlx_get_data_addr(lookat.sheet.ptr, &lookat.sheet.bpp, &lookat.sheet.size_line, &lookat.sheet.bpp);
	lookat.frame_w = 1280;
	lookat.frame_h = 720;
	lookat.num_frames = 44;
	lookat.frames_per_row = 4;
	lookat.curr_frame = 0;
	lookat.elapsed_time = 0;
	lookat.frame_time = 0.1f;
	lookat.x = 0;
	lookat.y = 0;
	game.lookat = &lookat;
	//TODO
	
	//TODO
	idle.sheet.ptr = mlx_xpm_file_to_image(game.mlx, "textures/idle_spritesheet.xpm", &frame_w, &frame_h);
	idle.sheet.data = mlx_get_data_addr(idle.sheet.ptr, &idle.sheet.bpp, &idle.sheet.size_line, &idle.sheet.bpp);
	idle.frame_w = 1280;
	idle.frame_h = 720;
	idle.num_frames = 16;
	idle.frames_per_row = 4;
	idle.curr_frame = 0;
	idle.elapsed_time = 0;
	idle.frame_time = 0.1f;
	idle.x = 0;
	idle.y = 0;
	game.idle = &idle;
	//TODO

	//TODO
	run.sheet.ptr = mlx_xpm_file_to_image(game.mlx, "textures/run_spritesheet.xpm", &frame_w, &frame_h);
	run.sheet.data = mlx_get_data_addr(run.sheet.ptr, &run.sheet.bpp, &run.sheet.size_line, &run.sheet.bpp);
	run.frame_w = 1280;
	run.frame_h = 720;
	run.num_frames = 10;
	run.frames_per_row = 5;
	run.curr_frame = 0;
	run.elapsed_time = 0;
	run.frame_time = 0.1f;
	run.x = 0;
	run.y = 0;
	game.run = &run;
	//TODO

	//TODO
	attack.sheet.ptr = mlx_xpm_file_to_image(game.mlx, "textures/attack_spritesheet.xpm", &frame_w, &frame_h);
	attack.sheet.data = mlx_get_data_addr(attack.sheet.ptr, &attack.sheet.bpp, &attack.sheet.size_line, &attack.sheet.bpp);
	attack.frame_w = 1280;
	attack.frame_h = 720;
	attack.num_frames = 14;
	attack.frames_per_row = 7;
	attack.curr_frame = 0;
	attack.elapsed_time = 0;
	attack.frame_time = 0.05f;
	attack.x = 0;
	attack.y = 0;
	game.attack = &attack;
	//TODO

	//TODO
	block.sheet.ptr = mlx_xpm_file_to_image(game.mlx, "textures/block_spritesheet.xpm", &frame_w, &frame_h);
	block.sheet.data = mlx_get_data_addr(block.sheet.ptr, &block.sheet.bpp, &block.sheet.size_line, &block.sheet.bpp);
	block.frame_w = 1280;
	block.frame_h = 720;
	block.num_frames = 8;
	block.frames_per_row = 4;
	block.curr_frame = 0;
	block.elapsed_time = 0;
	block.frame_time = 0.05f;
	block.x = 0;
	block.y = 0;
	game.block = &block;
	//TODO

	mlx_mouse_hook(game.win, mouse_hook, &game);
	mlx_loop_hook(game.mlx, &raycast_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
