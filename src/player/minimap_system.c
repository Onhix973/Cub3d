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
	center->x = game->minimap_width / 2;
	center->y = game->minimap_height / 2;
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
	if (delta.x > game->minimap_margin)
		game->minimap_cam.x += (delta.x - game->minimap_margin);
	else if (delta.x < -game->minimap_margin)
		game->minimap_cam.x += (delta.x + game->minimap_margin);
	if (delta.y > game->minimap_margin)
		game->minimap_cam.y += (delta.y - game->minimap_margin);
	else if (delta.y < -game->minimap_margin)
		game->minimap_cam.y += (delta.y + game->minimap_margin);
	max_offset.x = game->map_width * MINIMAP_SCALE - game->minimap_width;
	max_offset.y = game->map_height * MINIMAP_SCALE - game->minimap_height;
	if (max_offset.x <= 0)
		game->minimap_cam.x = 0;
	else if (game->minimap_cam.x < 0)
		game->minimap_cam.x = 0;
	else if (game->minimap_cam.x > max_offset.x)
		game->minimap_cam.x = max_offset.x;
	if (max_offset.y <= 0)
		game->minimap_cam.y = 0;
	else if (game->minimap_cam.y < 0)
		game->minimap_cam.y = 0;
	else if (game->minimap_cam.y > max_offset.y)
		game->minimap_cam.y = max_offset.y;
}

static inline bool	check_minimap_bounds(int x, int y, t_data *game)
{
	return (x >= MINIMAP_X && x < (MINIMAP_X + game->minimap_width) \
	&& y >= MINIMAP_Y && y < (MINIMAP_Y + game->minimap_height));
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
			if (check_minimap_bounds(draw.x, draw.y, game))
				img_pixel_put(draw.x, draw.y, color, &game->main_img);
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
	end->x = (game->minimap_cam.x + game->minimap_width) / MINIMAP_SCALE + 1;
	end->y = (game->minimap_cam.y + game->minimap_height) / MINIMAP_SCALE + 1;
	if (start->x < 0)
		start->x = 0;
	if (start->y < 0)
		start->y = 0;
	if (end->x > game->map_width)
		end->x = game->map_width;
	if (end->y > game->map_height)
		end->y = game->map_height;
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
			else if (game->map[m.y][m.x] == '\0' || game->map[m.y][m.x] == ' ')
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
			img_pixel_put(px + offset_x, py + offset_y, 0xFF0000, &game->main_img);
			offset_y++;
		}
		offset_x++;
	}
}
