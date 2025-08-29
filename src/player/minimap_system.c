#include "structs.h"
#include "cub3D.h"
#include "raycast.h"

#define MINIMAP_WIDTH 200
#define MINIMAP_HEIGHT 200

static void	draw_minimap_cell(t_data *game, int map_x, int map_y, int color)
{
	int	px;
	int	py;
	int offset_x = (int)(game->player->pos.x * MINIMAP_SCALE) - MINIMAP_WIDTH / 2;
	int offset_y = (int)(game->player->pos.y * MINIMAP_SCALE) - MINIMAP_HEIGHT / 2;

	py = 0;
	while (py < MINIMAP_SCALE)
	{
		px = 0;
		while (px < MINIMAP_SCALE)
		{
			img_pixel_put(MINIMAP_X + (map_x * MINIMAP_SCALE) - offset_x + px, \
			MINIMAP_Y + (map_y * MINIMAP_SCALE) - offset_y + py, color, game);
			px++;
		}
		py++;
	}

}

void	draw_entire_minimap(t_data *game)
{
	int	mx;
	int	my;
	int	color;

	my = 0;
	while (my < MAP_HEIGHT)
	{
		mx = 0;
		while (mx < MAP_WIDTH)
		{
			if (game->map[my][mx] == '1')
				color = 0xAAAAAA;
			else if (game->map[my][mx] == '\0')
			{
				mx++;
				continue ;
			}
			else
				color = 0x222222;
			draw_minimap_cell(game, mx, my, color);
			mx++;
		}
		my++;
	}
}

// void	draw_minimap_player(t_data *game)
// {
// 	int	px;
// 	int	py;
// 	int	offset_x;
// 	int	offset_y;

// 	px = MINIMAP_X + (int)(game->player->pos.x * MINIMAP_SCALE);
// 	py = MINIMAP_Y + (int)(game->player->pos.y * MINIMAP_SCALE);
// 	offset_x = -2;
// 	while (offset_x <= 2)
// 	{
// 		offset_y = -2;
// 		while (offset_y <= 2)
// 		{
// 			img_pixel_put(px + offset_x, py + offset_y, 0xFF0000, game);
// 			offset_y++;
// 		}
// 		offset_x++;
// 	}
// }

void draw_minimap_player(t_data *game)
{
    int px = MINIMAP_X + MINIMAP_WIDTH / 2;
    int py = MINIMAP_Y + MINIMAP_HEIGHT / 2;
    int offset_x = -2;
    int offset_y;

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


