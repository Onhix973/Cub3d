#include "structs.h"
#include "cub3D.h"
#include "raycast.h"

static inline bool	check_fs_map_bounds(int x, int y, t_data *game)
{
	return (x >= game->map_disp_set.fs_map_x \
	&& x < (game->map_disp_set.fs_map_x + game->map_disp_set.fs_map_width) \
	&& y >= game->map_disp_set.fs_map_y \
	&& y < (game->map_disp_set.fs_map_y + game->map_disp_set.fs_map_height));
}

void draw_fs_minimap_cell(t_data *game, int map_x, int map_y, int color)
{
	t_int_vector p;
	t_int_vector draw;

	p.y = 0;
	while (p.y < FS_MAP_SCALE)
	{
		p.x = 0;
		while (p.x < FS_MAP_SCALE)
		{
			draw.x = game->map_disp_set.fs_map_x + (map_x * FS_MAP_SCALE) \
			- game->map_disp_set.minimap_cam.x + p.x;
			draw.y = game->map_disp_set.fs_map_y + (map_y * FS_MAP_SCALE) \
			- game->map_disp_set.minimap_cam.y + p.y;
			if (check_fs_map_bounds(draw.x, draw.y, game))
				img_pixel_put(draw.x, draw.y, color, &game->main_img);
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
			if (game->map[m.y][m.x] == '\0' || game->map[m.y][m.x] == ' ')
			{
				m.x++;
				continue;
			}
			color = color_chooser(game, m);
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

	px = game->map_disp_set.fs_map_x + (int)(game->player->pos.x * FS_MAP_SCALE)
	 - game->map_disp_set.minimap_cam.x;
	py = game->map_disp_set.fs_map_y + (int)(game->player->pos.y * FS_MAP_SCALE)
	 - game->map_disp_set.minimap_cam.y;
	offset_x = -2;
	while (offset_x <= 2)
	{
		offset_y = -2;
		while (offset_y <= 2)
		{
			img_pixel_put(px + offset_x, py + offset_y, 
				0xFF0000, &game->main_img);
			offset_y++;
		}
		offset_x++;
	}
}
