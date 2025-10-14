#include <structs.h>
#include "cub3D.h"
#include "raycast.h"
#include <math.h>

static void facing_to_vector(t_facing face, t_vector *normal)
{
	if (face == NORTH)
	{
		normal->x = 0.0f;
		normal->y = -1.0f;
	}
	else if (face == SOUTH)
	{
		normal->x = 0.0f;
		normal->y = 1.0f;
	}
	else if (face == EAST)
	{
		normal->x = 1.0f;
		normal->y = 0.0f;
	}
	else if (face == WEST)
	{
		normal->x = -1.0f;
		normal->y = 0.0f;
	}
}

//TODO
#define PORTAL_WIDTH 0.5f
static bool	did_cross_portal(t_player *player, t_portal *portal)
{
	t_vector	normal;
	t_vector	curr;
	t_vector	prev;
	t_vector	tangent;
	float		lateral_distance;
	float		dot_curr;
	float		dot_prev;

	facing_to_vector(portal->face, &normal);
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

void	teleport_player_crossing_portal(t_data *game)
{
	t_portal	*in;
	t_portal	*out;
	t_player	*player;
	t_vector	rel;

	if (!game->portals.linked)
		return ;
	if (!did_cross_portal(player, in))	
		return ;

}

// void teleport_player_if_crossing(t_data *game) {
//     if (!game->portals.linked)
//         return;

//     t_portal *in = &game->portals.a;
//     t_portal *out = &game->portals.b;
//     t_player *player = game->player;

//     // Check if the player crossed the portal plane
//     if (!did_cross_portal(player, in))
//         return;

//     // Relative position from entrance portal
//     float rel_x = player->pos.x - in->world_x;
//     float rel_y = player->pos.y - in->world_y;

//     // Compute rotation angle between portals
//     float angle = calc_rotation_angle(in->face, out->face);

//     // Rotate relative position
//     float new_rel_x, new_rel_y;
//     rotate_vector(rel_x, rel_y, angle, &new_rel_x, &new_rel_y);

//     // Rotate player's view direction
//     float new_dir_x, new_dir_y;
//     rotate_vector(player->dir.x, player->dir.y, angle, &new_dir_x, &new_dir_y);

//     // Assign new position and direction
//     player->pos.x = out->world_x + new_rel_x;
//     player->pos.y = out->world_y + new_rel_y;
//     player->dir.x = new_dir_x;
//     player->dir.y = new_dir_y;

//     // Prevent immediate re-teleport by updating previous position
//     player->prev_pos = player->pos;
// }
