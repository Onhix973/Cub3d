#include "structs.h"
#include "raycast.h"

bool	is_player_moving(t_key_state *key_state)
{
	if (key_state->w || key_state->s || key_state->a || key_state->d)
		return (true);
	return (false);
}

static void	anim_administrator(t_sprite_sheet *anim, float delta_time, t_data *game,
		bool *state)
{
	update_sprite_sheet(anim, delta_time);
	draw_sprite_sheet_anim(anim, &game->main_img);
	if (!anim->looped \
	&& anim->curr_frame == anim->num_frames - 1)
		*state = false;
}

void	select_animation(t_data *game, float delta_time)
{
	if (game->g_states.attack_state)
		anim_administrator(&game->anims.attack, delta_time, game, &game->g_states.attack_state);
	else if (game->g_states.block_state)
		anim_administrator(&game->anims.block, delta_time, game, &game->g_states.block_state);
	else if (game->g_states.inspect)
		anim_administrator(&game->anims.lookat, delta_time, game, &game->g_states.inspect);
	else if (is_player_moving(game->key_state) && game->key_state->shift)
	{
		update_sprite_sheet(&game->anims.run, delta_time);
		draw_sprite_sheet_anim(&game->anims.run, &game->main_img);
	}
	else if (is_player_moving(game->key_state))
	{
		update_sprite_sheet(&game->anims.walk, delta_time);
		draw_sprite_sheet_anim(&game->anims.walk, &game->main_img);
	}
	else
	{
		update_sprite_sheet(&game->anims.idle, delta_time);
		draw_sprite_sheet_anim(&game->anims.idle, &game->main_img);
	}
}
