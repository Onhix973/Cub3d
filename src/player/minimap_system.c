#include "structs.h"
#include "cub3D.h"
#include "raycast.h"

void	init_top_view(t_int_vector *player, t_int_vector *center, \
	t_int_vector *delta, t_data *game)
{
	player->x = (int)(game->player->pos.x * MINIMAP_SCALE) \
	- game->minimap_cam.x;
	player->y = (int)(game->player->pos.y * MINIMAP_SCALE) \
	- game->minimap_cam.y;
	center->x = MINIMAP_WIDTH / 2;
	center->y = MINIMAP_HEIGHT / 2;
	delta->x = player->x - center->x;
	delta->y = player->y - center->y;
}

void	update_minimap_camera_offset(t_data *game)
{
	t_int_vector	player;
	t_int_vector	center;
	t_int_vector	delta;
	t_int_vector	max_offset;

	init_top_view(&player, &center, &delta, game);
	if (delta.x > MINIMAP_MARGIN)
		game->minimap_cam.x += (delta.x - MINIMAP_MARGIN);
	else if (delta.x < -MINIMAP_MARGIN)
		game->minimap_cam.x += (delta.x + MINIMAP_MARGIN);
	if (delta.y > MINIMAP_MARGIN)
		game->minimap_cam.y += (delta.y - MINIMAP_MARGIN);
	else if (delta.y < -MINIMAP_MARGIN)
		game->minimap_cam.y += (delta.y + MINIMAP_MARGIN);
	max_offset.x = MAP_WIDTH * MINIMAP_SCALE - MINIMAP_WIDTH;
	max_offset.y = MAP_HEIGHT * MINIMAP_SCALE - MINIMAP_HEIGHT;
	if (game->minimap_cam.x < 0)
		game->minimap_cam.x = 0;
	else if (game->minimap_cam.x > max_offset.x)
		game->minimap_cam.x = max_offset.x;
	if (game->minimap_cam.y < 0)
		game->minimap_cam.y = 0;
	else if (game->minimap_cam.y > max_offset.y)
		game->minimap_cam.y = max_offset.y;
}

static inline bool	check_minimap_bounds(int x, int y, bool fs)
{
	return (x >= MINIMAP_X && x < (MINIMAP_X + MINIMAP_WIDTH) \
	&& y >= MINIMAP_Y && y < (MINIMAP_Y + MINIMAP_HEIGHT));
}

static void draw_minimap_cell(t_data *game, int map_x, int map_y, int color)
{
	t_int_vector p;
	t_int_vector draw;

	p.y = 0;
	while (p.y < MINIMAP_SCALE)
	{
		p.x = 0;
		while (p.x < MINIMAP_SCALE)
		{
			draw.x = MINIMAP_X + (map_x * MINIMAP_SCALE) \
			- game->minimap_cam.x + p.x;
			draw.y = MINIMAP_Y + (map_y * MINIMAP_SCALE) \
			- game->minimap_cam.y + p.y;
			if (check_minimap_bounds(draw.x, draw.y, false))
				img_pixel_put(draw.x, draw.y, color, game);
			p.x++;
		}
		p.y++;
	}
}

void	init_minimap_settings(t_data *game, t_int_vector *start, \
    t_int_vector *end)
{
	start->x = game->minimap_cam.x / MINIMAP_SCALE;
	start->y = game->minimap_cam.y / MINIMAP_SCALE;
	end->x = (game->minimap_cam.x + MINIMAP_WIDTH) / MINIMAP_SCALE + 1;
	end->y = (game->minimap_cam.y + MINIMAP_HEIGHT) / MINIMAP_SCALE + 1;
	if (start->x < 0)
		start->x = 0;
	if (start->y < 0)
		start->y = 0;
	if (end->x > MAP_WIDTH)
		end->x = MAP_WIDTH;
	if (end->y > MAP_HEIGHT)
		end->y = MAP_HEIGHT;
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
			if (game->map[m.y][m.x] == '1')
				color = 0xAAAAAA;
			else if (game->map[m.y][m.x] == '\0')
			{
				m.x++;
				continue;
			}
			else
				color = 0x222222;
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
	int	offset_x = -2;
	int	offset_y;

	px = MINIMAP_X + (int)(game->player->pos.x * MINIMAP_SCALE) \
	- game->minimap_cam.x;
	py = MINIMAP_Y + (int)(game->player->pos.y * MINIMAP_SCALE) \
	- game->minimap_cam.y;
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
