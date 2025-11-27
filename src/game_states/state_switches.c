#include "structs.h"
#include "raycast.h"
#include "cub3D.h"

static void	map_states_switch(t_data *game)
{
	if (game->key_state->tab && !game->g_states.fs_map)
	{
		game->key_state->tab = false;
		game->g_states.fs_map = true;
	}
	else if (game->key_state->tab && game->g_states.fs_map)
	{
		game->key_state->tab = false;
		game->g_states.fs_map = false;
	}
}

static void animations_states_switch_helper(t_data *game)
{
	if (game->key_state->e && !game->g_states.attack_state 
	&& !game->g_states.block_state && !game->g_states.inspect)
	{
		game->key_state->e = false;
		game->g_states.attack_state = true;
		game->g_states.attack_triggered = true;
		game->anims.attack.curr_frame = 0;
	}
	if (game->key_state->q && !game->g_states.block_state 
		&& !game->g_states.attack_state && !game->g_states.inspect)
	{
		game->key_state->q = false;
		game->g_states.block_state = true;
		game->anims.block.curr_frame = 0;
	}
	if (is_player_moving(game->key_state))
	{
		game->g_states.afk_triggered = false;
		game->g_states.afk_state = false;
	}
}

static void	animations_states_switch(t_data *game)
{
	struct timeval now;
	long	elapsed;

	gettimeofday(&now, NULL);
	elapsed = now.tv_sec - game->key_state->last_user_input.tv_sec;
	if (elapsed > AFK_THRESHOLD && !game->g_states.afk_state 
		&& !game->g_states.afk_triggered && !is_player_moving(game->key_state))
	{
		game->g_states.afk_state = true;
		game->anims.afk.curr_frame = 0;
		game->g_states.afk_triggered = true;
	}
	if (game->key_state->l && !game->g_states.inspect)
	{
		game->key_state->l = false;
		game->g_states.inspect = true;
		game->anims.lookat.curr_frame = 0;
	}
	animations_states_switch_helper(game);
}

static void	portal_deactivator(t_data *game)
{
	if (!hitboxes_checker(game, game->player->pos.x, game->player->pos.y))
		return ;
	if (game->key_state->r)
	{
		game->key_state->r = false;
		game->portals.a.active = false;
		game->portals.b.active = false;
		game->portals.linked = false;
	}
}

void	game_states_mswitch(t_data *game)
{
	map_states_switch(game);
	animations_states_switch(game);
	portal_deactivator(game);
}