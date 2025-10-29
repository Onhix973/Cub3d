#include "cub3D.h"
#include "structs.h"
#include "raycast.h"
#include <sys/time.h>
#include <X11/X.h>

static bool	hitboxes_checker(t_data *game, float x, float y)
{
	t_player	*player;

	player = game->player;
	if (game->map[(int)(y + HITBOX_OFFSET)][(int)x] == '0' \
	&& game->map[(int)(y - HITBOX_OFFSET)][(int)x] == '0' \
	&& game->map[(int)y][(int)(x + HITBOX_OFFSET)] == '0'\
	&& game->map[(int)y][(int)(x - HITBOX_OFFSET)] == '0')
		return (true);
	return (false);
}

void	compute_delta_pos(t_data *game, t_vector *delta_pos, float move_speed, \
			float delta_time)
{
	if (game->key_state->w)
	{
		delta_pos->x += game->player->dir.x * move_speed * delta_time;
		delta_pos->y += game->player->dir.y * move_speed * delta_time;
	}
	if (game->key_state->s)
	{
		delta_pos->x -= game->player->dir.x * move_speed * delta_time;
		delta_pos->y -= game->player->dir.y * move_speed * delta_time;
	}
	if (game->key_state->d)
	{
		delta_pos->x += (-game->player->dir.y) * move_speed * delta_time;
		delta_pos->y += game->player->dir.x * move_speed * delta_time;
	}
	if (game->key_state->a)
	{
		delta_pos->x += (game->player->dir.y) * move_speed * delta_time;
		delta_pos->y += (-game->player->dir.x) * move_speed * delta_time;
	}
}

void	compute_rot_angle(t_data *game, float delta_time)
{
	if (game->key_state->left)
	{
		rotate_vector(&game->player->dir, -ROTATION_SPEED * delta_time);
		rotate_vector(&game->player->camera_plane, \
			-ROTATION_SPEED * delta_time);
	}
	if (game->key_state->right)
	{
		rotate_vector(&game->player->dir, ROTATION_SPEED * delta_time);
		rotate_vector(&game->player->camera_plane, \
			ROTATION_SPEED * delta_time);
	}
}

#include <stdio.h>

int update_player(t_data *game, float delta_time)
{
	float		sprint_multiplier;
	float		move_speed;
	t_vector	new_pos;
	t_vector	delta_pos;

	game->player->prev_pos = game->player->pos;
	if (game->key_state->shift)
		sprint_multiplier = 2.0f;
	else
		sprint_multiplier = 1.0f;
	delta_pos.x = 0.0f;
	delta_pos.y = 0.0f;
	move_speed = BASE_MOVE_SPEED * sprint_multiplier;
	compute_delta_pos(game, &delta_pos, move_speed, delta_time);
	new_pos.x = game->player->pos.x + delta_pos.x;
	new_pos.y = game->player->pos.y + delta_pos.y;
	compute_rot_angle(game, delta_time);
	if ((player_hb_intersects_with_segment(game->player, &game->portals.a) 
	|| player_hb_intersects_with_segment(game->player, &game->portals.b)) && game->portals.linked)
	{
		game->player->pos.x = new_pos.x;
		game->player->pos.y = new_pos.y;
	}
	else
	{
		if (hitboxes_checker(game, new_pos.x, game->player->pos.y))
			game->player->pos.x = new_pos.x;
		if (hitboxes_checker(game, game->player->pos.x, new_pos.y))
			game->player->pos.y = new_pos.y;
	}
	return (0);
}
