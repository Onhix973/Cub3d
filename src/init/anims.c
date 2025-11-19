#include "raycast.h"
#include "cub3D.h"
#include "structs.h"
#include <mlx.h>

bool	set_image_and_data(t_data *game, t_sprite_sheet *anim, \
	char *anim_identifier)
{
	int	frame_w;
	int	frame_h;

	anim->sheet.ptr = mlx_xpm_file_to_image(game->mlx, anim_identifier, \
		&frame_w, &frame_h);
	if (!anim->sheet.ptr)
		return (false);
	anim->sheet.data = mlx_get_data_addr(anim->sheet.ptr, &anim->sheet.bpp, \
		&anim->sheet.size_line, &anim->sheet.bpp);
	if (!anim->sheet.data)
		return (false);
	return (true);
}

bool	init_idle(t_data* game)
{
	t_sprite_sheet	*idle;

	idle = &game->anims.idle;
	if (!set_image_and_data(game, idle, IDLE_ANIM_PATH))
		return (false);
	idle->frame_w = 1280;
	idle->frame_h = 720;
	idle->num_frames = 16;
	idle->frames_per_row = 4;
	idle->curr_frame = 0;
	idle->elapsed_time = 0;
	idle->frame_time = 0.1f;
	idle->x = 0;
	idle->y = 0;
	idle->looped = true;
	return (true);
}

bool	init_walk(t_data* game)
{
	t_sprite_sheet	*walk;

	walk = &game->anims.walk;
	if (!set_image_and_data(game, walk, WALK_ANIM_PATH))
		return (false);
	walk->frame_w = 1280;
	walk->frame_h = 400;
	walk->num_frames = 10;
	walk->frames_per_row = 10;
	walk->curr_frame = 0;
	walk->elapsed_time = 0;
	walk->frame_time = 0.1f;
	walk->x = 0;
	walk->y = 320;
	walk->looped = true;
	return (true);
}

bool	init_run(t_data* game)
{
	t_sprite_sheet	*run;

	run = &game->anims.run;
	if (!set_image_and_data(game, run, RUN_ANIM_PATH))
		return (false);
	run->frame_w = 1280;
	run->frame_h = 720;
	run->num_frames = 10;
	run->frames_per_row = 5;
	run->curr_frame = 0;
	run->elapsed_time = 0;
	run->frame_time = 0.1f;
	run->x = 0;
	run->y = 0;
	run->looped = true;
	return (true);
}

bool	init_lookat(t_data* game)
{
	t_sprite_sheet	*lookat;

	lookat = &game->anims.lookat;
	if (!set_image_and_data(game, lookat, LOOKAT_ANIM_PATH))
		return (false);
	lookat->frame_w = 1280;
	lookat->frame_h = 720;
	lookat->num_frames = 44;
	lookat->frames_per_row = 4;
	lookat->curr_frame = 0;
	lookat->elapsed_time = 0;
	lookat->frame_time = 0.1f;
	lookat->x = 0;
	lookat->y = 0;
	lookat->looped = false;
	return (true);
}

bool	init_attack(t_data* game)
{
	t_sprite_sheet	*attack;

	attack = &game->anims.attack;
	if (!set_image_and_data(game, attack, ATTACK_ANIM_PATH))
		return (false);
	attack->frame_w = 1280;
	attack->frame_h = 720;
	attack->num_frames = 14;
	attack->frames_per_row = 7;
	attack->curr_frame = 0;
	attack->elapsed_time = 0;
	attack->frame_time = 0.05f;
	attack->x = 0;
	attack->y = 0;
	attack->looped = false;
	return (true);
}

bool	init_block(t_data* game)
{
	t_sprite_sheet	*block;

	block = &game->anims.block;
	if (!set_image_and_data(game, block, BLOCK_ANIM_PATH))
		return (false);
	block->frame_w = 1280;
	block->frame_h = 720;
	block->num_frames = 8;
	block->frames_per_row = 4;
	block->curr_frame = 0;
	block->elapsed_time = 0;
	block->frame_time = 0.05f;
	block->x = 0;
	block->y = 0;
	block->looped = false;
	return (true);
}

bool	init_afk(t_data* game)
{
	t_sprite_sheet	*afk;

	afk = &game->anims.afk;
	if (!set_image_and_data(game, afk, AFK_ANIM_PATH))
		return (false);
	afk->frame_w = 1280;
	afk->frame_h = 720;
	afk->num_frames = 40;
	afk->frames_per_row = 8;
	afk->curr_frame = 0;
	afk->elapsed_time = 0;
	afk->frame_time = 0.1f;
	afk->x = 0;
	afk->y = 0;
	afk->looped = false;
	return (true);
}

bool	init_spritesheets(t_data* game)
{
	if (!init_idle(game))
		return (false);
	if (!init_walk(game))
		return (false);
	if (!init_run(game))
		return (false);
	if (!init_lookat(game))
		return (false);
	if (!init_attack(game))
		return (false);
	if (!init_block(game))
		return (false);
	if (!init_afk(game))
		return (false);
	return (true);
}