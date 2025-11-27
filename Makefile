COLOR_GREEN = \033[0;32m
COLOR_RED = \033[0;31m
COLOR_YELLOW = \033[0;33m
COLOR_BLUE = \033[0;34m
COLOR_PURPLE = \033[0;35m
COLOR_CYAN = \033[0;36m
COLOR_RESET = \033[0m


#################################################
INVALID_DIR = invalid_headers
TEST_FILES = $(wildcard $(INVALID_DIR)/*.cub)
#################################################

NAME = cub3D

INCFLAG = -I
CFLAGS = -Wall -Werror -Wextra -MMD -MP
MLX_FLAGS = -lX11 -lXext -lXfixes
OPTI_FLAGS = -g3 -O3
MATHS_FLAGS = -lm
CC = cc

LIBFTDIR = 42Libft/
MLXDIR = minilibx-linux/
LIBFTINCDIR = $(LIBFTDIR)includes/

LIBFTHEADER = $(LIBFTINCDIR)libft.h \
				$(LIBFTINCDIR)get_next_line.h
LIBFT = $(LIBFTDIR)libft.a
MLX = $(MLXDIR)libmlx_Linux.a

HEADERSDIR = includes/

HEADERS = $(HEADERSDIR)cub3D.h \
			$(HEADERSDIR)parsing.h \
			$(HEADERSDIR)raycast.h \
			$(HEADERSDIR)structs.h

SRCSDIR = src/
SRCS = main.c \
		utils/config_init.c utils/count_fields.c utils/free_split.c utils/ft_error.c utils/ft_isspace.c utils/ft_split_keep_char.c \
		utils/ft_strjoin_re.c utils/map_free.c utils/parse_header_utils.c utils/parse_rgb.c utils/rgb_to_hex.c \
		parsing/check_args.c parsing/context_creator.c parsing/flood_fill.c parsing/load_lines.c \
		parsing/parse_header_helper.c parsing/parse_header.c parsing/parsing_map_build.c parsing/parsing_map_syntax.c \
		raycast/vectors_routines_utils.c raycast/vectors_routines.c \
		raycast/raycast.c raycast/raycast_utils.c raycast/frame_utils.c portals/creator.c portals/hitbox_checks.c\
		player/moves.c player/rotation.c player/key_events.c minimap/minimap_system.c minimap/minimap_drawing.c\
		fs_map/fs_map_system.c fs_map/fs_map_drawing.c cleanup/clean_and_exit.c cleanup/cleanup_utils.c init/mlx.c init/player.c init/anims.c init/game_settings.c init/anims_utils.c\
		raycast/texture_mapping.c player/teleport_player.c game_states/state_switches.c \
		anims/spritesheet_painter.c anims/anims_switches.c

OBJSDIR = .build/

OBJS = $(patsubst %.c, $(OBJSDIR)%.o,$(SRCS))
DEPS = $(patsubst %.o, %.d, $(OBJS))

TOTAL_SRCS := $(words $(SRCS))
COMPILED_SRCS := 0

.PHONY : all
all : $(NAME)

-include $(DEPS)

$(NAME) : $(OBJS) $(LIBFT) $(MLX)
	@echo "\n$(COLOR_GREEN)Linking objects...$(COLOR_RESET)"
	@$(CC) $(OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS) $(MATHS_FLAGS) $(CFLAGS) $(OPTI_FLAGS) -o $(NAME)
	@echo "$(COLOR_RED)$(NAME) compiled !$(COLOR_RESET)"

$(OBJSDIR)%.o : $(SRCSDIR)%.c $(HEADERSDIR) $(LIBFT) $(MLX) | $(OBJSDIR)
	@mkdir -p $(dir $@)
	@$(eval COMPILED_SRCS=$(shell echo $$(($(COMPILED_SRCS)+1))))
	@printf "\rCompiling $(NAME): [%-50s] %d/%d " \
	"$(shell printf '#%.0s' $$(seq 1 $$(($(COMPILED_SRCS)*50/$(TOTAL_SRCS)))))" \
	$(COMPILED_SRCS) $(TOTAL_SRCS)
	@$(CC) -o $@ -c $< $(CFLAGS) $(INCFLAG)$(HEADERSDIR) $(INCFLAG)$(LIBFTINCDIR) $(OPTI_FLAGS) $(INCFLAG)$(MLXDIR)

$(OBJSDIR) :
	@mkdir -p $(OBJSDIR)

$(LIBFT) : force
	@make -j -sC $(LIBFTDIR)

$(MLX) :
	@make -j -sC $(MLXDIR)

.PHONY : norme
norme :
	norminette $(SRCSDIR) $(LIBFTDIR) $(HEADERSDIR)

.PHONY : clean
clean :
	@echo "$(COLOR_BLUE)Cleaning objects...$(COLOR_RESET)"
	@rm -rf $(OBJSDIR)
	@make clean -sC $(LIBFTDIR)
	@make clean -sC mapgen

.PHONY : fclean
fclean : clean
	@echo "$(COLOR_CYAN)Cleaning executable...$(COLOR_RESET)"
	@rm -f $(NAME)
	@make fclean -sC $(LIBFTDIR)
	@make clean -sC $(MLXDIR)
	@make fclean -sC mapgen

force :
	@true

.PHONY : re
re : fclean all

play : all
	@make -j -sC mapgen && mapgen/./mapgen > out.cub && ./cub3D out.cub

replay :
	@./cub3D out.cub

##################################################
test: $(NAME)
	rm -f errors.log
	@for file in $(TEST_FILES); do \
		echo "Running test with $$file..."; \
		valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) $$file 2>> errors.log ; \
		echo ""; \
	done