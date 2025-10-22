#include "cub3D.h"
#include "structs.h"
#include "raycast.h"
#include <sys/time.h>
#include <X11/X.h>

//TODO CLEAN THAT BECAUSE IT LOOKS REALLY UGLY
bool is_portal_tile(t_data *game, float check_x, float check_y)
{
	t_portal *portal_a = &game->portals.a;
	t_portal *portal_b = &game->portals.b;

	int	tile_x = (int)check_x;
	int	tile_y = (int)check_y;
	int	x_testa = portal_a->world_x;
	int	y_testa = portal_a->world_y;
	if (portal_a->facing == EAST)
		x_testa -= 1.0f;
	if (portal_a->facing == SOUTH)
		y_testa -= 1.0f;
	int	x_testb = portal_b->world_x;
	int	y_testb = portal_b->world_y;
	if (portal_b->facing == EAST)
		x_testb -= 1.0f;
	if (portal_b->facing == SOUTH)
		y_testb -= 1.0f;
	if (portal_a->active && portal_b->active \
		&& tile_x == x_testa && tile_y == y_testa)
		return (true);
	if (portal_b->active && portal_a->active \
		&& tile_x == x_testb && tile_y == y_testb)
		return (true);
	return (false);
}

bool vertical_hitboxes_checker(t_data *game, float new_y)
{
	t_player	*player;

	player = game->player;
	if ((game->map[(int)(new_y + HITBOX_OFFSET)][(int)(player->pos.x)] == '0' || 
		is_portal_tile(game, player->pos.x, new_y + HITBOX_OFFSET)) && \
		(game->map[(int)(new_y - HITBOX_OFFSET)][(int)(player->pos.x)] == '0' ||
		is_portal_tile(game, player->pos.x, new_y - HITBOX_OFFSET)) && \
		(game->map[(int)(new_y)][(int)(player->pos.x + HITBOX_OFFSET)] == '0' ||
		is_portal_tile(game, player->pos.x + HITBOX_OFFSET, new_y)) && \
		(game->map[(int)(new_y)][(int)(player->pos.x - HITBOX_OFFSET)] == '0' ||
		is_portal_tile(game, player->pos.x - HITBOX_OFFSET, new_y)))
		return (true);
	return (false);
}

bool horizontal_hitboxes_checker(t_data *game, float new_x)
{
	t_player	*player;

	player = game->player;
	if ((game->map[(int)(player->pos.y + HITBOX_OFFSET)][(int)(new_x)] == '0' ||
		is_portal_tile(game, new_x, player->pos.y + HITBOX_OFFSET)) && \
		(game->map[(int)(player->pos.y - HITBOX_OFFSET)][(int)(new_x)] == '0' ||
		is_portal_tile(game, new_x, player->pos.y - HITBOX_OFFSET)) && \
		(game->map[(int)(player->pos.y)][(int)(new_x + HITBOX_OFFSET)] == '0' ||
		is_portal_tile(game, new_x + HITBOX_OFFSET, player->pos.y)) && \
		(game->map[(int)(player->pos.y)][(int)(new_x - HITBOX_OFFSET)] == '0' ||
		is_portal_tile(game, new_x - HITBOX_OFFSET, player->pos.y)))
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

int update_player(t_data *game, float delta_time)
{
	float		sprint_multiplier;
	float		move_speed;
	t_vector	new_pos;
	t_vector	delta_pos;
	bool		on_portal;
	bool		correct_move_x = false;
	bool		correct_move_y = false;
	bool		crossing_a = false;
	bool		crossing_b = false;
	bool		can_move = true;

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
	if (horizontal_hitboxes_checker(game, new_pos.x))
		correct_move_x = true;
	if (vertical_hitboxes_checker(game, new_pos.y))
		correct_move_y = true;
	on_portal = 
    is_portal_tile(game, game->player->pos.x + HITBOX_OFFSET, game->player->pos.y) ||
    is_portal_tile(game, game->player->pos.x - HITBOX_OFFSET, game->player->pos.y) ||
    is_portal_tile(game, game->player->pos.x, game->player->pos.y + HITBOX_OFFSET) ||
    is_portal_tile(game, game->player->pos.x, game->player->pos.y - HITBOX_OFFSET);
	if (on_portal)
	{
		crossing_a = did_cross_portal(game->player, &game->portals.a) && is_crossing_correct_side(game->player, &game->portals.a);
		crossing_b = did_cross_portal(game->player, &game->portals.b) && is_crossing_correct_side(game->player, &game->portals.b);
		bool crossing = crossing_a || crossing_b;
		can_move = !on_portal || crossing || (on_portal && !crossing);
	}
	if (can_move)
	{
		if (correct_move_x)
			game->player->pos.x = new_pos.x;
		if (correct_move_y)
			game->player->pos.y = new_pos.y;
	}
	return (0);
}
