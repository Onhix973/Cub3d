#include "structs.h"
#include "cub3D.h"
#include "raycast.h"

void	init_fs_top_view(t_int_vector *player, t_int_vector *center, \
	t_int_vector *delta, t_data *game)
{
	player->x = (int)(game->player->pos.x * FS_MAP_SCALE) \
	- game->map_disp_set.minimap_cam.x;
	player->y = (int)(game->player->pos.y * FS_MAP_SCALE) \
	- game->map_disp_set.minimap_cam.y;
	center->x = game->map_disp_set.fs_map_width >> 1;
	center->y = game->map_disp_set.fs_map_height >> 1;
	delta->x = player->x - center->x;
	delta->y = player->y - center->y;
	if (delta->x > FS_MAP_MARGIN)
		game->map_disp_set.minimap_cam.x += (delta->x - FS_MAP_MARGIN);
	else if (delta->x < -FS_MAP_MARGIN)
		game->map_disp_set.minimap_cam.x += (delta->x + FS_MAP_MARGIN);
	if (delta->y > FS_MAP_MARGIN)
		game->map_disp_set.minimap_cam.y += (delta->y - FS_MAP_MARGIN);
	else if (delta->y < -FS_MAP_MARGIN)
		game->map_disp_set.minimap_cam.y += (delta->y + FS_MAP_MARGIN);
}

void	update_fs_minimap_camera_offset(t_data *game)
{
	t_int_vector	player;
	t_int_vector	center;
	t_int_vector	delta;
	t_int_vector	max_offset;

	init_fs_top_view(&player, &center, &delta, game);
	max_offset.x = game->map_disp_set.map_width * FS_MAP_SCALE \
	- game->map_disp_set.fs_map_width;
	max_offset.y = game->map_disp_set.map_height * FS_MAP_SCALE \
	- game->map_disp_set.fs_map_height;
	if (max_offset.x <= 0)
		game->map_disp_set.minimap_cam.x = 0;
	else if (game->map_disp_set.minimap_cam.x < 0)
		game->map_disp_set.minimap_cam.x = 0;
	else if (game->map_disp_set.minimap_cam.x > max_offset.x)
		game->map_disp_set.minimap_cam.x = max_offset.x;
	if (max_offset.y <= 0)
		game->map_disp_set.minimap_cam.y = 0;
	else if (game->map_disp_set.minimap_cam.y < 0)
		game->map_disp_set.minimap_cam.y = 0;
	else if (game->map_disp_set.minimap_cam.y > max_offset.y)
		game->map_disp_set.minimap_cam.y = max_offset.y;
}

void	init_fs_minimap_settings(t_data *game, t_int_vector *start, \
	t_int_vector *end)
{
	start->x = game->map_disp_set.minimap_cam.x / FS_MAP_SCALE;
	start->y = game->map_disp_set.minimap_cam.y / FS_MAP_SCALE;
	end->x = (game->map_disp_set.minimap_cam.x \
		+ game->map_disp_set.fs_map_width) / FS_MAP_SCALE + 1;
	end->y = (game->map_disp_set.minimap_cam.y \
		+ game->map_disp_set.fs_map_height) / FS_MAP_SCALE + 1;
	if (start->x < 0)
		start->x = 0;
	if (start->y < 0)
		start->y = 0;
	if (end->x > game->map_disp_set.map_width)
		end->x = game->map_disp_set.map_width;
	if (end->y > game->map_disp_set.map_height)
		end->y = game->map_disp_set.map_height;
}
