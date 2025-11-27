#include "structs.h"
#include "raycast.h"
#include "cub3D.h"

static inline bool	check_minimap_bounds(int x, int y, t_data *game)
{
	return (x >= MINIMAP_X && x < (MINIMAP_X + game->map_disp_set.minimap_width)
		&& y >= MINIMAP_Y && y < (MINIMAP_Y
			+ game->map_disp_set.minimap_height));
}

void	draw_minimap_cell(t_data *game, int map_x, int map_y, int color)
{
	t_int_vector	p;
	t_int_vector	draw;

	p.y = 0;
	while (p.y < MINIMAP_SCALE)
	{
		p.x = 0;
		while (p.x < MINIMAP_SCALE)
		{
			draw.x = MINIMAP_X + (map_x * MINIMAP_SCALE)
				- game->map_disp_set.minimap_cam.x + p.x;
			draw.y = MINIMAP_Y + (map_y * MINIMAP_SCALE)
				- game->map_disp_set.minimap_cam.y + p.y;
			if (check_minimap_bounds(draw.x, draw.y, game))
				img_pixel_put(draw.x, draw.y, color, &game->main_img);
			p.x++;
		}
		p.y++;
	}
}

int	color_chooser(t_data *game, t_int_vector m)
{
	int	color;

	if (game->map[m.y][m.x] == '1')
		color = 0xAAAAAA;
	else
		color = 0x222222;
	return (color);
}

void	draw_entire_minimap(t_data *game)
{
	t_int_vector	start;
	t_int_vector	end;
	t_int_vector	m;
	int				color;

	init_minimap_settings(game, &start, &end);
	m.y = start.y;
	while (m.y < end.y)
	{
		m.x = start.x;
		while (m.x < end.x)
		{
			if (game->map[m.y][m.x] == '\n' || game->map[m.y][m.x] == ' ')
			{
				m.x++;
				continue ;
			}
			color = color_chooser(game, m);
			draw_minimap_cell(game, m.x, m.y, color);
			m.x++;
		}
		m.y++;
	}
}

void	draw_minimap_player(t_data *game)
{
	int	px;
	int	py;
	int	offset_x;
	int	offset_y;

	offset_x = -2;
	px = MINIMAP_X + (int)(game->player->pos.x * MINIMAP_SCALE)
		- game->map_disp_set.minimap_cam.x;
	py = MINIMAP_Y + (int)(game->player->pos.y * MINIMAP_SCALE)
		- game->map_disp_set.minimap_cam.y;
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
