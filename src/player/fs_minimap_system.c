#include "structs.h"
#include "cub3D.h"
#include "raycast.h"

void	update_fs_map_camera(t_data *game)
{
	game->minimap_cam.x = 0;
	game->minimap_cam.y = 0;
}

void    init_fs_minimap_settings(t_data *game, t_int_vector *start, \
    t_int_vector *end)
{
    start->x = game->minimap_cam.x / FS_MAP_SCALE;
    start->y = game->minimap_cam.y / FS_MAP_SCALE;
    end->x = (game->minimap_cam.x + FS_MAP_WIDTH) / FS_MAP_SCALE + 1;
    end->y = (game->minimap_cam.y + FS_MAP_HEIGHT) / FS_MAP_SCALE + 1;
    if (start->x < 0)
        start->x = 0;
    if (start->y < 0)
        start->y = 0;
    if (end->x > MAP_WIDTH)
        end->x = MAP_WIDTH;
    if (end->y > MAP_HEIGHT)
        end->y = MAP_HEIGHT;
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
            draw.x = FS_MAP_X + (map_x * FS_MAP_SCALE) \
			- game->minimap_cam.x + p.x;
            draw.y = FS_MAP_Y + (map_y * FS_MAP_SCALE) \
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
			else if (game->map[m.y][m.x] == '\0')
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

	px = FS_MAP_X + (int)(game->player->pos.x * FS_MAP_SCALE) \
	- game->minimap_cam.x;
	py = FS_MAP_Y + (int)(game->player->pos.y * FS_MAP_SCALE) \
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
