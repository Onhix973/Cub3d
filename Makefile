# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/28 15:04:28 by tlutz             #+#    #+#              #
#    Updated: 2025/11/28 17:31:22 by tlutz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COLOR_GREEN = \033[0;32m
COLOR_RED = \033[0;31m
COLOR_YELLOW = \033[0;33m
COLOR_BLUE = \033[0;34m
COLOR_PURPLE = \033[0;35m
COLOR_CYAN = \033[0;36m
COLOR_RESET = \033[0m

NAME = cub3D
NAME_BONUS = cub3D_bonus

INCFLAG = -I
CFLAGS = -Wall -Wextra -Werror -MMD -MP -O3
MLX_FLAGS = -lX11 -lXext -lXfixes
MATHS_FLAGS = -lm
CC = cc

LIBFTDIR = 42Libft/
MLXDIR = minilibx-linux/
LIBFTINCDIR = $(LIBFTDIR)includes/

LIBFTHEADER = $(LIBFTINCDIR)libft.h \
				$(LIBFTINCDIR)get_next_line.h

LIBFT = $(LIBFTDIR)libft.a
MLX = $(MLXDIR)libmlx_Linux.a

HEADERSDIR = mandatory/includes/

HEADERS_BONUS_DIR = bonus/includes/

HEADERS = $(HEADERSDIR)cub3D.h \
			$(HEADERSDIR)parsing.h \
			$(HEADERSDIR)raycast.h \
			$(HEADERSDIR)structs.h

HEADERS_BONUS = $(HEADERS_BONUS_DIR)cub3D.h \
			$(HEADERSBONUS_DIR)parsing.h \
			$(HEADERSBONUS_DIR)raycast.h \
			$(HEADERSBONUS_DIR)structs.h

SRCS_BONUS_DIR = bonus/src/

SRCS_BONUS_MAIN = main.c

SRCS_BONUS_ANIMS = anims/spritesheet_painter.c anims/anims_switches.c

SRCS_BONUS_CLEANUP = cleanup/clean_and_exit.c cleanup/cleanup_utils.c

SRCS_BONUS_FS_MAP = fs_map/fs_map_system.c fs_map/fs_map_drawing.c

SRCS_BONUS_GAME_STATES = game_states/maps_state.c game_states/state_switches.c

SRCS_BONUS_INIT = init/mlx.c init/player.c init/anims.c init/game_settings.c init/anims_utils.c

SRCS_BONUS_MINIMAP = minimap/minimap_system.c minimap/minimap_drawing.c

SRCS_BONUS_PARSING = parsing/check_args.c parsing/context_creator.c parsing/flood_fill.c parsing/load_lines.c \
					parsing/parse_header_helper.c parsing/parse_header.c parsing/parsing_map_build.c parsing/parsing_map_syntax.c

SRCS_BONUS_PLAYER = player/moves.c player/rotation.c player/key_events.c player/teleport_player.c player/teleport_player_utils.c

SRCS_BONUS_PORTALS = portals/creator.c portals/hitbox_checks.c

SRCS_BONUS_RAYCAST = raycast/vectors_routines_utils.c raycast/vectors_routines.c \
					raycast/raycast.c raycast/raycast_utils.c raycast/frame_utils.c raycast/texture_mapping.c \
					raycast/drawing_utils.c raycast/texture_mapping_portals.c

SRCS_BONUS_UTILS = utils/config_init.c utils/free_split.c utils/ft_error.c utils/ft_isspace.c utils/ft_split_keep_char.c \
					utils/ft_strjoin_re.c utils/map_free.c utils/parse_header_utils.c utils/parse_rgb.c utils/rgb_to_hex.c

SRCS_BONUS = $(SRCS_BONUS_ANIMS) \
		$(SRCS_BONUS_CLEANUP) \
		$(SRCS_BONUS_FS_MAP) \
		$(SRCS_BONUS_GAME_STATES) \
		$(SRCS_BONUS_INIT) \
		$(SRCS_BONUS_MAIN) \
		$(SRCS_BONUS_MINIMAP) \
		$(SRCS_BONUS_PARSING) \
		$(SRCS_BONUS_PLAYER) \
		$(SRCS_BONUS_PORTALS) \
		$(SRCS_BONUS_RAYCAST) \
		$(SRCS_BONUS_UTILS)

SRCS_DIR = mandatory/src/
SRCS = main.c cleanup/clean_and_exit.c cleanup/cleanup_utils.c init/game_settings.c init/mlx.c init/player.c \
		parsing/check_args.c parsing/context_creator.c parsing/flood_fill.c parsing/load_lines.c \
		parsing/parse_header_helper.c parsing/parse_header.c parsing/parsing_map_build.c parsing/parsing_map_syntax.c \
		player/key_events.c player/moves.c player/rotation.c \
		raycast/vectors_routines_utils.c raycast/vectors_routines.c raycast/raycast.c raycast/raycast_utils.c \
		raycast/frame_utils.c raycast/texture_mapping.c raycast/drawing_utils.c \
		utils/config_init.c utils/free_split.c utils/ft_error.c utils/ft_isspace.c utils/ft_split_keep_char.c \
		utils/ft_strjoin_re.c utils/map_free.c utils/parse_header_utils.c utils/parse_rgb.c utils/rgb_to_hex.c
		

OBJSDIR = .build/
OBJS_BONUS_DIR = .build_bonus/

OBJS = $(patsubst %.c, $(OBJSDIR)%.o,$(SRCS))
DEPS = $(patsubst %.o, %.d, $(OBJS))

OBJS_BONUS = $(patsubst %.c, $(OBJS_BONUS_DIR)%.o,$(SRCS_BONUS))
DEPS_BONUS = $(patsubst %.o, %.d, $(OBJS_BONUS))

TOTAL_SRCS := $(words $(SRCS))
COMPILED_SRCS := 0

TOTAL_SRCS_BONUS := $(words $(SRCS_BONUS))
COMPILED_SRCS_BONUS := 0

.PHONY : all
all : $(NAME)

-include $(DEPS)

$(NAME) : $(OBJS) $(LIBFT) $(MLX)
	@echo "\n$(COLOR_GREEN)Linking objects...$(COLOR_RESET)"
	@$(CC) $(OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS) $(MATHS_FLAGS) $(CFLAGS) -o $(NAME)
	@echo "$(COLOR_RED)$(NAME) compiled !$(COLOR_RESET)"

$(OBJSDIR)%.o : $(SRCS_DIR)%.c $(LIBFT) $(MLX) | $(OBJSDIR)
	@mkdir -p $(dir $@)
	@$(eval COMPILED_SRCS=$(shell echo $$(($(COMPILED_SRCS)+1))))
	@printf "\rCompiling $(NAME): [%-50s] %d/%d " \
	"$(shell printf '#%.0s' $$(seq 1 $$(($(COMPILED_SRCS)*50/$(TOTAL_SRCS)))))" \
	$(COMPILED_SRCS) $(TOTAL_SRCS)
	@$(CC) -o $@ -c $< $(CFLAGS) $(INCFLAG)$(HEADERSDIR) $(INCFLAG)$(LIBFTINCDIR) $(INCFLAG)$(MLXDIR)

$(OBJSDIR) :
	@mkdir -p $(OBJSDIR)

$(OBJS_BONUS_DIR) :
	@mkdir -p $(OBJS_BONUS_DIR)

.PHONY : bonus
bonus : $(NAME_BONUS)

-include $(DEPS_BONUS)

$(NAME_BONUS) : $(OBJS_BONUS) $(LIBFT) $(MLX)
	@echo "\n$(COLOR_GREEN)Linking bonus objects...$(COLOR_RESET)"
	@$(CC) $(OBJS_BONUS) $(LIBFT) $(MLX) $(MLX_FLAGS) $(MATHS_FLAGS) $(CFLAGS) -o $(NAME_BONUS)
	@echo "$(COLOR_RED)$(NAME_BONUS) compiled !$(COLOR_RESET)"

$(OBJS_BONUS_DIR)%.o : $(SRCS_BONUS_DIR)%.c $(LIBFT) $(MLX) | $(OBJS_BONUS_DIR)
	@mkdir -p $(dir $@)
	@$(eval COMPILED_SRCS_BONUS=$(shell echo $$(($(COMPILED_SRCS_BONUS)+1))))
	@printf "\rCompiling $(NAME_BONUS): [%-50s] %d/%d " \
	"$(shell printf '#%.0s' $$(seq 1 $$(($(COMPILED_SRCS_BONUS)*50/$(TOTAL_SRCS_BONUS)))))" \
	$(COMPILED_SRCS_BONUS) $(TOTAL_SRCS_BONUS)
	@$(CC) -o $@ -c $< $(CFLAGS) $(INCFLAG)$(HEADERS_BONUS_DIR) $(INCFLAG)$(LIBFTINCDIR) $(INCFLAG)$(MLXDIR)

$(LIBFT) : force
	@make -j -sC $(LIBFTDIR)

$(MLX) :
	@make -j -sC $(MLXDIR)

.PHONY : norme
norme :
	norminette $(SRCSDIR) $(LIBFTDIR) $(SRCS_BONUS_DIR)

.PHONY : fcleanmg
fcleanmg :
	@make fclean -sC bonus/mapgen

.PHONY : clean
clean :
	@echo "$(COLOR_BLUE)Cleaning objects...$(COLOR_RESET)"
	@rm -rf $(OBJSDIR) $(OBJS_BONUS_DIR)
	@make clean -sC $(LIBFTDIR)

.PHONY : fclean
fclean : clean
	@echo "$(COLOR_CYAN)Cleaning executables...$(COLOR_RESET)"
	@rm -f $(NAME) $(NAME_BONUS)
	@make fclean -sC $(LIBFTDIR)
	@make clean -sC $(MLXDIR)

force :
	@true

.PHONY : re
re : fclean all

play : bonus
	@make -j -sC bonus/mapgen && bonus/mapgen/mapgen > out.cub && ./cub3D_bonus out.cub

replay :
	@./cub3D_bonus out.cub
