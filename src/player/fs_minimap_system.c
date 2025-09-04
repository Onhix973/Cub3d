#include "structs.h"
#include "cub3D.h"
#include "raycast.h"

void	init_fs_top_view(t_int_vector *player, t_int_vector *center, \
	t_int_vector *delta, t_data *game)
{
	player->x = (int)(game->player->pos.x * FS_MAP_SCALE) \
	- game->minimap_cam.x;
	player->y = (int)(game->player->pos.y * FS_MAP_SCALE) \
	- game->minimap_cam.y;
	center->x = game->fs_map_width / 2;
	center->y = game->fs_map_height / 2;
	delta->x = player->x - center->x;
	delta->y = player->y - center->y;
}

void	update_fs_minimap_camera_offset(t_data *game)
{
	t_int_vector	player;
	t_int_vector	center;
	t_int_vector	delta;
	t_int_vector	max_offset;

	init_fs_top_view(&player, &center, &delta, game);
	if (delta.x > FS_MAP_MARGIN)
		game->minimap_cam.x += (delta.x - FS_MAP_MARGIN);
	else if (delta.x < -FS_MAP_MARGIN)
		game->minimap_cam.x += (delta.x + FS_MAP_MARGIN);
	if (delta.y > FS_MAP_MARGIN)
		game->minimap_cam.y += (delta.y - MINIMAP_MARGIN);
	else if (delta.y < -FS_MAP_MARGIN)
		game->minimap_cam.y += (delta.y + FS_MAP_MARGIN);
	max_offset.x = game->map_width * FS_MAP_SCALE - game->fs_map_width;
	max_offset.y = game->map_height * FS_MAP_SCALE - game->fs_map_height;
	if (game->minimap_cam.x < 0)
		game->minimap_cam.x = 0;
	else if (game->minimap_cam.x > max_offset.x)
		game->minimap_cam.x = max_offset.x;
	if (game->minimap_cam.y < 0)
		game->minimap_cam.y = 0;
	else if (game->minimap_cam.y > max_offset.y)
		game->minimap_cam.y = max_offset.y;
}

void    init_fs_minimap_settings(t_data *game, t_int_vector *start, \
    t_int_vector *end)
{
    start->x = game->minimap_cam.x / FS_MAP_SCALE;
    start->y = game->minimap_cam.y / FS_MAP_SCALE;
    end->x = (game->minimap_cam.x + game->fs_map_width) / FS_MAP_SCALE + 1;
    end->y = (game->minimap_cam.y + game->fs_map_height) / FS_MAP_SCALE + 1;
    if (start->x < 0)
        start->x = 0;
    if (start->y < 0)
        start->y = 0;
    if (end->x > game->map_width)
        end->x = game->map_width;
    if (end->y > game->map_height)
        end->y = game->map_height;
}

static void draw_fs_minimap_cell(t_data *game, int map_x, int map_y, int color)
{
    t_int_vector p;
    t_int_vector draw;

    p.y = 0;
    while (p.y < FS_MAP_SCALE)
    {
        p.x = 0;
        while (p.x < FS_MAP_SCALE)
        {
            draw.x = game->fs_map_x + (map_x * FS_MAP_SCALE) \
			- game->minimap_cam.x + p.x;
            draw.y = game->fs_map_y + (map_y * FS_MAP_SCALE) \
			- game->minimap_cam.y + p.y;
			img_pixel_put(draw.x, draw.y, color, game);
            p.x++;
        }
        p.y++;
    }
}

void draw_fs_minimap(t_data *game)
{
	t_int_vector	start;
	t_int_vector	end;
	t_int_vector	m;
	int				color;

	init_fs_minimap_settings(game, &start, &end);
	m.y = start.y;
	while (m.y < end.y)
	{
		m.x = start.x;
		while (m.x < end.x)
		{
			if (game->map[m.y][m.x] == '1')
				color = 0xAAAAAA;
			else if (game->map[m.y][m.x] == '\0' || game->map[m.y][m.x] == ' ')
			{
				m.x++;
				continue;
			}
			else
				color = 0x222222;
			draw_fs_minimap_cell(game, m.x, m.y, color);
			m.x++;
		}
		m.y++;
	}
}

void	draw_fs_minimap_player(t_data *game)
{
	int	px;
	int	py;
	int	offset_x;
	int	offset_y;

	px = game->fs_map_x + (int)(game->player->pos.x * FS_MAP_SCALE) \
	- game->minimap_cam.x;
	py = game->fs_map_y + (int)(game->player->pos.y * FS_MAP_SCALE) \
	- game->minimap_cam.y;
	offset_x = -2;
	while (offset_x <= 2)
	{
		offset_y = -2;
		while (offset_y <= 2)
		{
			img_pixel_put(px + offset_x, py + offset_y, 0xFF0000, game);
			offset_y++;
		}
		offset_x++;
	}
}
