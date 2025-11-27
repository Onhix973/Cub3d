#include "structs.h"
#include "cub3D.h"
#include "raycast.h"

void	init_top_view(t_int_vector *player, t_int_vector *center,
	t_int_vector *delta, t_data *game)
{
	player->x = (int)(game->player->pos.x * MINIMAP_SCALE)
		- game->map_disp_set.minimap_cam.x;
	player->y = (int)(game->player->pos.y * MINIMAP_SCALE)
		- game->map_disp_set.minimap_cam.y;
	center->x = game->map_disp_set.minimap_width >> 1;
	center->y = game->map_disp_set.minimap_height >> 1;
	delta->x = player->x - center->x;
	delta->y = player->y - center->y;
}

void	update_minimap_camera_offset_helper(t_int_vector *max_offset,
	t_map_disp_set *map_sett)
{
	if (max_offset->x <= 0)
		map_sett->minimap_cam.x = 0;
	else if (map_sett->minimap_cam.x < 0)
		map_sett->minimap_cam.x = 0;
	else if (map_sett->minimap_cam.x > max_offset->x)
		map_sett->minimap_cam.x = max_offset->x;
	if (max_offset->y <= 0)
		map_sett->minimap_cam.y = 0;
	else if (map_sett->minimap_cam.y < 0)
		map_sett->minimap_cam.y = 0;
	else if (map_sett->minimap_cam.y > max_offset->y)
		map_sett->minimap_cam.y = max_offset->y;
}

void	update_minimap_camera_offset(t_data *game)
{
	t_int_vector	player;
	t_int_vector	center;
	t_int_vector	delta;
	t_int_vector	max_offset;
	t_map_disp_set	*map_sett;

	map_sett = &game->map_disp_set;
	init_top_view(&player, &center, &delta, game);
	if (delta.x > map_sett->minimap_margin)
		map_sett->minimap_cam.x += (delta.x - map_sett->minimap_margin);
	else if (delta.x < -map_sett->minimap_margin)
		map_sett->minimap_cam.x += (delta.x + map_sett->minimap_margin);
	if (delta.y > map_sett->minimap_margin)
		map_sett->minimap_cam.y += (delta.y - map_sett->minimap_margin);
	else if (delta.y < -map_sett->minimap_margin)
		map_sett->minimap_cam.y += (delta.y + map_sett->minimap_margin);
	max_offset.x = map_sett->map_width
		* MINIMAP_SCALE - map_sett->minimap_width;
	max_offset.y = map_sett->map_height
		* MINIMAP_SCALE - map_sett->minimap_height;
	update_minimap_camera_offset_helper(&max_offset, map_sett);
}

void	init_minimap_settings(t_data *game, t_int_vector *start,
	t_int_vector *end)
{
	start->x = game->map_disp_set.minimap_cam.x / MINIMAP_SCALE;
	start->y = game->map_disp_set.minimap_cam.y / MINIMAP_SCALE;
	end->x = (game->map_disp_set.minimap_cam.x
			+ game->map_disp_set.minimap_width) / MINIMAP_SCALE + 1;
	end->y = (game->map_disp_set.minimap_cam.y
			+ game->map_disp_set.minimap_height) / MINIMAP_SCALE + 1;
	if (start->x < 0)
		start->x = 0;
	if (start->y < 0)
		start->y = 0;
	if (end->x > game->map_disp_set.map_width)
		end->x = game->map_disp_set.map_width;
	if (end->y > game->map_disp_set.map_height)
		end->y = game->map_disp_set.map_height;
}
