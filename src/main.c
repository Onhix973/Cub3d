#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include "cub3D.h"
#include "parsing.h"
#include "raycast.h"
#include "mlx.h"
#include "libft.h"
#include <X11/keysym.h>
#include <X11/X.h>
#include <math.h>
#include <sys/time.h>
#include <X11/extensions/Xfixes.h>

int	mouse_hook(int button, int x, int y, void *param)
{
	t_data *game;
	
	(void)y;
	(void)x;
	game = (t_data *)param;
	if (button == 1)
	{
		if (!game->g_states.attack_state && !game->g_states.block_state \
			&& !game->g_states.inspect)
		{
			game->g_states.attack_state = true;
			game->g_states.attack_triggered = true;
			game->anims.attack.curr_frame = 0;
		}
	}
	else if (button == 3)
	{
		if (!game->g_states.block_state && !game->g_states.attack_state \
			&& !game->g_states.inspect)
		{
			game->g_states.block_state = true;
			game->anims.block.curr_frame = 0;
		}
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_context 	ctx;
	t_data 		game;
	t_player	player;
	t_key_state	key_states;
	t_texture	portal;

	ft_memset(&key_states, 0, sizeof(t_key_state));
	ft_memset(&game, 0, sizeof(t_data));
	context_creator(argc, argv, &ctx);
	game.player = &player;
	game.map = ctx.map.grid;
	game.key_state = &key_states;
	if (!init_game(&game, &ctx))
		return (24);
	//TODO
	portal.texture = mlx_xpm_file_to_image(game.mlx, "textures/portal.xpm", &portal.width, &portal.height);
	portal.data = mlx_get_data_addr(portal.texture, &portal.bpp, &portal.size_line, &portal.endian);
	game.portal = portal;
	//TODO
	mlx_mouse_hook(game.win, mouse_hook, &game);
	mlx_loop_hook(game.mlx, &raycast_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
