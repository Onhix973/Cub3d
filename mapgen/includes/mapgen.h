/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapgen.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:58:21 by abonifac          #+#    #+#             */
/*   Updated: 2025/11/28 15:08:08 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPGEN_H
# define MAPGEN_H

# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define BOLD	"\033[1m"
# define RESET   "\033[0m"
# define MALLOC_ERR "Error:\nMemory allocation failed\n"
# define ARGS_ERR "Error:\nWidth and height must be positive integers\n"

# define BORDER_W '2'
# define DICE_SIZE 32

typedef enum e_card
{
	N,
	S,
	W,
	E
}	t_card;

typedef struct s_mapgen
{
	char	**map;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	int		first_pos[2];
	int		area;
}	t_mapgen;

typedef struct s_rand_dir
{
	int	dice[DICE_SIZE];
	int	count;
	int	weight;
	int	k;
	int	new_x;
	int	new_y;
	int	direction;
}	t_rand_dir;

/* UTILS */
void	border_walls(t_mapgen *cfg, char c);
int		convert_args(char **av, int ac, t_mapgen *config);
void	free_split(char **split);

void	rand_position_player(t_mapgen *cfg);
int		biased_rand_dir(t_mapgen *cfg, int px, int py);

void	init_config(t_mapgen *config);
void	init_rand_dir(t_rand_dir *rd);
void	print_map(char **map);
void	update_player_direction(t_mapgen *cfg);
int		write_error(const char *message);
int		read_int_from_stdin(const char *prompt);

#endif