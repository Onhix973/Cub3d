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
CFLAGS = -Wall -Werror -Wextra -g3
MLX_FLAGS = -lX11 -lXext -lXfixes
OPTI_FLAGS = -g3
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
		\
		parsing/check_args.c parsing/context_creator.c parsing/flood_fill.c parsing/load_lines.c \
		parsing/parse_header_helper.c parsing/parse_header.c parsing/parsing_map_build.c parsing/parsing_map_syntax.c \
		raycast/vectors_routines_utils.c raycast/vectors_routines.c \
		raycast/raycast.c raycast/raycast_utils.c raycast/frame_utils.c player/portals.c\
		player/moves.c player/rotation.c player/key_events.c player/minimap_system.c\
		player/fs_minimap_system.c cleanup/clean_and_exit.c init/mlx.c init/player.c init/anims.c init/game_settings.c\
		raycast/texture_mapping.c player/teleport_player.c
OBJSDIR = .build/

OBJS = $(patsubst %.c, $(OBJSDIR)%.o,$(SRCS))

TOTAL_SRCS := $(words $(SRCS))
COMPILED_SRCS := 0

.PHONY : all
all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT) $(MLX)
	@echo "\n$(COLOR_GREEN)Linking objects...$(COLOR_RESET)"
	@$(CC) $(OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS) $(MATHS_FLAGS) $(CFLAGS) $(OPTI_FLAGS) -o $(NAME)
	@echo "$(COLOR_RED)$(NAME) compiled !$(COLOR_RESET)"

$(OBJSDIR)%.o : $(SRCSDIR)%.c $(HEADERS) $(LIBFT) $(MLX) | $(OBJSDIR)
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

.PHONY : fclean
fclean : clean
	@echo "$(COLOR_CYAN)Cleaning executable...$(COLOR_RESET)"
	@rm -f $(NAME)
	@make fclean -sC $(LIBFTDIR)
	@make clean -sC $(MLXDIR)

force :
	@true

.PHONY : re
re : fclean all


##################################################
test: $(NAME)
	rm -f errors.log
	@for file in $(TEST_FILES); do \
		echo "Running test with $$file..."; \
		valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) $$file 2>> errors.log ; \
		echo ""; \
	done