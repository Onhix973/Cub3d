#include "structs.h"
#include "raycast.h"
#include "cub3D.h"
#include <math.h>

float	compute_rotation_angle(t_vector *v1, t_vector *v2)
{
	float	dot;
	float	cross;

	dot = dot_product(*v1, *v2);
	cross = v1->x * v2->y - v1->y * v2->x;
	return (atan2f(cross, dot));
}

static void	rotate_vectors(t_vector *relative_pos, t_player *player,
	float angle)
{
	rotate_vector(relative_pos, angle);
	rotate_vector(&player->dir, angle);
	rotate_vector(&player->camera_plane, angle);
}

static void	get_rot_angle_and_rotate(t_portal *in, t_portal *out,
	t_player *player, t_vector *relative_pos)
{
	t_vector	in_facing_vec;
	t_vector	out_facing_vec;
	t_vector	in_dir;
	float		angle;

	facing_to_vector(in->facing, &in_facing_vec);
	facing_to_vector(out->facing, &out_facing_vec);
	in_dir.x = -in_facing_vec.x;
	in_dir.y = -in_facing_vec.y;
	angle = compute_rotation_angle(&in_dir, &out_facing_vec);
	rotate_vectors(relative_pos, player, angle);
}

static float	clamp_relative_tangent(float relative_tangent)
{
	if (relative_tangent > PORTAL_HALF_WIDTH)
		return (PORTAL_HALF_WIDTH);
	else if (relative_tangent < -PORTAL_HALF_WIDTH)
		return (-PORTAL_HALF_WIDTH);
	else
		return (relative_tangent);
}

void	teleport_to_portal(t_portal *in, t_portal *out, t_player *player)
{
	t_vector	relative_pos;
	t_vector	out_normal;
	t_vector	out_tangent;
	float		relative_normal;
	float		relative_tangent;

	relative_pos.x = player->pos.x - in->world_x ;
	relative_pos.y = player->pos.y - in->world_y;
	get_rot_angle_and_rotate(in, out, player, &relative_pos);
	facing_to_vector(out->facing, &out_normal);
	out_tangent.x = -out_normal.y;
	out_tangent.y = out_normal.x;
	relative_normal = relative_pos.x * out_normal.x
		+ relative_pos.y * out_normal.y;
	relative_tangent = relative_pos.x * out_tangent.x
		+ relative_pos.y * out_tangent.y;
	relative_tangent = clamp_relative_tangent(relative_tangent);
	relative_pos.x = out_normal.x * relative_normal
		- out_tangent.x * relative_tangent;
	relative_pos.y = out_normal.y * relative_normal
		- out_tangent.y * relative_tangent;
	player->pos.x = out->world_x + relative_pos.x;
	player->pos.y = out->world_y + relative_pos.y;
	player->prev_pos = player->pos;
}
