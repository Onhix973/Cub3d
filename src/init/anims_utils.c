#include "cub3D.h"
#include "structs.h"
#include "raycast.h"

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
