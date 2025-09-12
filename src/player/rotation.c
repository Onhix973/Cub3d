#include "cub3D.h"
#include "structs.h"
#include <math.h>
#include "mlx.h"

void	rotate_vector(t_vector *v, float angle)
{
	float	oldx; 

	oldx= v->x;
	v->x = v->x * cosf(angle) - v->y * sinf(angle);
	v->y = oldx * sinf(angle) + v->y * cosf(angle);
}

int	focus_out_handler(t_data *game)
{
	game->key_state->w = false;
	game->key_state->a = false;
	game->key_state->s = false;
	game->key_state->d = false;
	game->key_state->left = false;
	game->key_state->right = false;
	game->key_state->shift = false;
	game->key_state->c = false;
	game->key_state->v = false;
	return (0);
}

int mouse_handler(int x, int y, void *param)
{
	(void)y;
	t_data	*game = (t_data *)param;
	static int ignore_mouse_event = 0;
	int		delta_x;
	float	angle;

	if (!game->mouse_activated)
		return (0);
	if (ignore_mouse_event)
	{
		ignore_mouse_event = 0;
		return (0);
	}
	delta_x = x - WIN_WIDTH * 0.5;
	angle = delta_x * MOUSE_SENSITIVITY;
	rotate_vector(&game->player->dir, angle);
	rotate_vector(&game->player->camera_plane, angle);
	mlx_mouse_move(game->mlx, game->win, WIN_WIDTH * 0.5, WIN_HEIGHT * 0.5);
	return (0);
}