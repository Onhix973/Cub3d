#include "structs.h"
#include "raycast.h"
#include "cub3D.h"
#include <math.h>

t_vector	get_portal_center(t_portal *portal)
{
	t_vector	center;

	center.x = (portal->segment_start.x + portal->segment_end.x) / 2.0;
	center.y = (portal->segment_start.y + portal->segment_end.y) / 2.0;
	return (center);
}

float	get_portal_normal_angle(t_portal *portal)
{
	t_vector	dir;

	dir.x = portal->segment_end.x - portal->segment_start.x;
	dir.y = portal->segment_end.y - portal->segment_start.y;
	return (atan2(dir.y, dir.x) + M_PI / 2.0);
}

t_vector	get_portal_normal_vector(t_portal *portal)
{
	float		angle;
	t_vector	normal;

	angle = get_portal_normal_angle(portal);
	normal.x = cos(angle);
	normal.y = sin(angle);
	return (normal);
}

void	setup_portal_camera(t_portal *in, t_portal *out, t_player *player)
{
	t_vector	in_center;
	t_vector	out_center;
	float		rotation_angle;
	t_vector	relative_pos;
	t_vector	in_normal;
	t_vector	out_normal;

	in_center = get_portal_center(in);
	out_center = get_portal_center(out);
	in_normal = get_portal_normal_vector(in);
	out_normal = get_portal_normal_vector(out);
	relative_pos.x = player->pos.x - in_center.x;
	relative_pos.y = player->pos.y - in_center.y;
	rotation_angle = compute_rotation_angle(&in_normal, &out_normal) + M_PI;
	rotate_vector(&relative_pos, rotation_angle);
	out->virtual_cam.pos.x = out_center.x + relative_pos.x;
	out->virtual_cam.pos.y = out_center.y + relative_pos.y;
	out->virtual_cam.dir = player->dir;
	rotate_vector(&out->virtual_cam.dir, rotation_angle);
	out->virtual_cam.camera_plane = player->camera_plane;
	rotate_vector(&out->virtual_cam.camera_plane, rotation_angle);
}

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
