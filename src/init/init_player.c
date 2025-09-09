#include "structs.h"
#include "cub3D.h"
#include "math.h"
#include "raycast.h"

static void	compute_player_angle(t_data *game)
{
	game->player->angle = 0.0f;
	if (game->ctx->map.player_dir == 'N')
		game->player->angle = M_PI / 2;
	if (game->ctx->map.player_dir == 'E')
		game->player->angle = 0;
	if (game->ctx->map.player_dir == 'S')
		game->player->angle = (3 * M_PI) / 2;
	if (game->ctx->map.player_dir == 'W')
		game->player->angle = M_PI;
}

void	init_player(t_data *game, t_player *player)
{
	game->player = player;
	compute_player_angle(game);
	player->dir = get_direction_from_angle(player->angle);
	player->plane.x = -player->dir.y * tan(FOV / 2);
	player->plane.y = player->dir.x * tan(FOV / 2);
	player->pos.x = (float)game->ctx->map.player_x + 0.5;
	player->pos.y = (float)game->ctx->map.player_y + 0.5;
	game->ctx->map.grid[game->ctx->map.player_y][game->ctx->map.player_x] = '0';
}