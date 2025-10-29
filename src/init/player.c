#include "structs.h"
#include "cub3D.h"
#include "math.h"
#include "raycast.h"

static void	compute_player_angle(t_player *player, t_context *ctx)
{
	player->angle = 0.0f;
	if (ctx->map.player_dir == 'N')
		player->angle = M_PI / 2;
	if (ctx->map.player_dir == 'E')
		player->angle = 0;
	if (ctx->map.player_dir == 'S')
		player->angle = (3 * M_PI) / 2;
	if (ctx->map.player_dir == 'W')
		player->angle = M_PI;
}

void	init_player(t_player *player, t_context *ctx)
{
	compute_player_angle(player, ctx);
	player->dir = get_direction_from_angle(player->angle);
	player->camera_plane.x = -player->dir.y * tan(FOV / 2);
	player->camera_plane.y = player->dir.x * tan(FOV / 2);
	player->pos.x = (float)ctx->map.player_x + 0.5;
	player->pos.y = (float)ctx->map.player_y + 0.5;
}