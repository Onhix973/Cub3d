#include "structs.h"
#include "raycast.h"

bool	is_player_moving(t_key_state *key_state)
{
	if (key_state->w || key_state->s || key_state->a || key_state->d)
		return (true);
	return (false);
}

static void	anim_administrator(t_sprite_sheet *anim, float delta_time,
	t_data *game, bool *state)
{
	update_sprite_sheet(anim, delta_time);
	draw_sprite_sheet_anim(anim, &game->main_img);
	if (!anim->looped && anim->curr_frame == anim->num_frames - 1)
		*state = false;
}

void	update_anim_wrapper(float delta_time, t_img *main_img,
	t_sprite_sheet *anim)
{
	update_sprite_sheet(anim, delta_time);
	draw_sprite_sheet_anim(anim, main_img);
}

void	select_animation(t_data *game, float delta_time)
{
	if (game->g_states.afk_state)
		anim_administrator(&game->anims.afk, delta_time, game,
			&game->g_states.afk_state);
	else if (game->g_states.attack_state)
		anim_administrator(&game->anims.attack, delta_time, game,
			&game->g_states.attack_state);
	else if (game->g_states.block_state)
		anim_administrator(&game->anims.block, delta_time, game,
			&game->g_states.block_state);
	else if (game->g_states.inspect)
		anim_administrator(&game->anims.lookat, delta_time, game,
			&game->g_states.inspect);
	else if (is_player_moving(game->key_state) && game->key_state->shift)
		update_anim_wrapper(delta_time, &game->main_img, &game->anims.run);
	else if (is_player_moving(game->key_state))
		update_anim_wrapper(delta_time, &game->main_img, &game->anims.walk);
	else
		update_anim_wrapper(delta_time, &game->main_img, &game->anims.idle);
}
