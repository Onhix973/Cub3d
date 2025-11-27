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
		return (write_error(IMAGE_LOAD_ERR));
	anim->sheet.data = mlx_get_data_addr(anim->sheet.ptr, &anim->sheet.bpp, \
		&anim->sheet.size_line, &anim->sheet.bpp);
	if (!anim->sheet.data)
		return (write_error(DATA_IMG_ERR));
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
