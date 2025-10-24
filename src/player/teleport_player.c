#include <structs.h>
#include "cub3D.h"
#include "raycast.h"
#include <math.h>

static void facing_to_vector(t_facing face, t_vector *vector)
{
	if (face == NORTH)
	{
		vector->x = 0.0f;
		vector->y = -1.0f;
	}
	else if (face == SOUTH)
	{
		vector->x = 0.0f;
		vector->y = 1.0f;
	}
	else if (face == EAST)
	{
		vector->x = 1.0f;
		vector->y = 0.0f;
	}
	else if (face == WEST)
	{
		vector->x = -1.0f;
		vector->y = 0.0f;
	}
}

bool	is_crossing_correct_side(t_player *player, t_portal *portal)
{
	t_vector	normal;
	t_vector	move;
	float		move_len;
	float		dot_move_normal;

	facing_to_vector(portal->facing, &normal);
	normalize_vector(normal);
	move.x = player->pos.x - player->prev_pos.x;
	move.y = player->pos.y - player->prev_pos.y;
	move_len = vector_length(move);
	if (move_len == 0)
		return (false);
	move.x /= move_len;
	move.y /= move_len;
	dot_move_normal = dot_product(move, normal);
	return (dot_move_normal < 0.0f);
}

bool	did_cross_portal(t_player *player, t_portal *portal)
{
	t_vector	normal;
	t_vector	curr;
	t_vector	prev;
	t_vector	tangent;
	float		lateral_distance;
	float		dot_curr;
	float		dot_prev;

	facing_to_vector(portal->facing, &normal);
	curr.x = player->pos.x - portal->world_x;
	curr.y = player->pos.y - portal->world_y;
	prev.x = player->prev_pos.x - portal->world_x;
	prev.y = player->prev_pos.y - portal->world_y;
	dot_curr = dot_product(curr, normal);
	dot_prev = dot_product(prev, normal);
	if (dot_prev > 0.0f && dot_curr <= 0.0f)
	{
		tangent.x = -normal.y;
		tangent.y = normal.x;
		lateral_distance = fabsf(dot_product(curr, tangent));
		if (lateral_distance < PORTAL_WIDTH)
			return (true);
	}
	return (false);
}

float	compute_rotation_angle(t_vector *v1, t_vector *v2)
{
	float	dot;
	float	cross;

	dot = dot_product(*v1, *v2);
	cross = v1->x * v2->y - v1->y * v2->x;
	return (atan2f(cross, dot));
}

//TODO
#include <stdio.h>
void	teleport_to_portal(t_portal *in, t_portal *out, t_player *player)
{
	t_vector	in_facing_vec;
	t_vector	out_facing_vec;
	t_vector	relative_pos;
	t_vector	out_normal;
	t_vector	out_tangent;
	float		angle;
	float		relative_normal;
	float		relative_tangent;

	relative_pos.x = player->pos.x - in->world_x ;
	relative_pos.y = player->pos.y - in->world_y;
	facing_to_vector(in->facing, &in_facing_vec);
	facing_to_vector(out->facing, &out_facing_vec);
	angle = compute_rotation_angle(&in_facing_vec, &out_facing_vec) + M_PI;
	rotate_vector(&relative_pos, angle);
	rotate_vector(&player->dir, angle);
	rotate_vector(&player->camera_plane, angle);
	facing_to_vector(out->facing, &out_normal);
	out_tangent.x = -out_normal.y;
	out_tangent.y = out_normal.x;
	relative_normal = relative_pos.x * out_normal.x + relative_pos.y * out_normal.y;
	relative_tangent = relative_pos.x * out_tangent.x + relative_pos.y * out_tangent.y;
	if (relative_tangent > PORTAL_WIDTH / 2.0f)
		relative_tangent = PORTAL_WIDTH / 2.0f;
	else if (relative_tangent < -PORTAL_WIDTH / 2.0f)
		relative_tangent = -PORTAL_WIDTH / 2.0f;
	relative_pos.x = out_normal.x * relative_normal - out_tangent.x * relative_tangent;
	relative_pos.y = out_normal.y * relative_normal - out_tangent.y * relative_tangent;
	player->pos.x = out->world_x + relative_pos.x;
	player->pos.y = out->world_y + relative_pos.y;
	player->prev_pos = player->pos;
}

void	teleport_player_crossing_portal(t_data *game)
{
	if (!game->portals.linked)
		return ;
	if (did_cross_portal(game->player, &game->portals.a))	
		teleport_to_portal(&game->portals.a, &game->portals.b, game->player);
	else if (did_cross_portal(game->player, &game->portals.b))
		teleport_to_portal(&game->portals.b, &game->portals.a, game->player);
}
