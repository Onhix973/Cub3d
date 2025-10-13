#include "structs.h"
#include "cub3D.h"
#include "raycast.h"
#include <X11/keysym.h>
#include <stdlib.h>

void	handle_game_keys(t_key_state *key_state, int keycode)
{
	if (keycode == XK_w)
		key_state->w = true;
	if (keycode == XK_a)
		key_state->a = true;
	if (keycode == XK_s)
		key_state->s = true;
	if (keycode == XK_d)
		key_state->d = true;
	if (keycode == XK_Left)
		key_state->left = true;
	if (keycode == XK_Right)
		key_state->right = true;
	if (keycode == XK_Shift_L)
		key_state->shift = true;
	if (keycode == XK_c)
		key_state->c = true;
	if (keycode == XK_v)
		key_state->v = true;
	if (keycode == XK_l)
		key_state->l = true;
	if (keycode == XK_e)
		key_state->e = true;
	if (keycode == XK_q)
		key_state->q = true;
	//TODO
	// if (keycode == XK_Tab)
	// 	key_state->tab = true;
}

int	key_press(int keycode, void *param)
{
	t_data	*game;

	game = (t_data *)param;
	if (keycode == XK_Escape)
		exit_game(game);
	else
		handle_game_keys(game->key_state, keycode);
	return (0);
}

int	key_release(int keycode, void *param)
{
	t_key_state	*key_state;

	key_state = (t_key_state *)param;
	if (keycode == XK_w)
		key_state->w = false;
	if (keycode == XK_a)
		key_state->a = false;
	if (keycode == XK_s)
		key_state->s = false;
	if (keycode == XK_d)
		key_state->d = false;
	if (keycode == XK_Left)
		key_state->left = false;
	if (keycode == XK_Right)
		key_state->right = false;
	if (keycode == XK_Shift_L)
		key_state->shift = false;
	if (keycode == XK_c)
		key_state->c = false;
	if (keycode == XK_v)
		key_state->v = false;
	if (keycode == XK_Tab)
		key_state->tab = true;
	// if (keycode == XK_e)
	// 	key_state->e = false;
	// if (keycode == XK_q)
	// 	key_state->q = false;
	return (0);
}
