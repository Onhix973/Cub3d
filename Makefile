COLOR_GREEN = \033[0;32m
COLOR_RED = \033[0;31m
COLOR_YELLOW = \033[0;33m
COLOR_BLUE = \033[0;34m
COLOR_PURPLE = \033[0;35m
COLOR_CYAN = \033[0;36m
COLOR_RESET = \033[0m

NAME = cub3D

INCFLAG = -I
CFLAGS = -Wall -Werror -Wextra -g3 -O3
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

HEADERSDIR = includes/

HEADERS = $(HEADERSDIR)cub3D.h \
			$(HEADERSDIR)parsing.h \
			$(HEADERSDIR)raycast.h \
			$(HEADERSDIR)structs.h \
			$(HEADERSDIR)gnl_noleak.h

SRCSDIR = src/
SRCS = main.c \
		utils/ft_error.c utils/ft_split_keep_char.c utils/ft_isspace.c utils/config_init.c  utils/parse_rgb.c utils/map_free.c utils/free_split.c \
		parsing/parsing.c parsing/check_args.c parsing/new_parsing.c parsing/parsing_map_build.c  parsing/parsing_map_syntax.c parsing/flood_fill.c \
		gnl_noleak/get_next_line.c gnl_noleak/get_next_line_utils.c \
		raycast/vectors_routines_utils.c raycast/vectors_routines.c \
		raycast/raycast.c raycast/raycast_utils.c raycast/frame_utils.c\
		player/moves.c player/rotation.c player/key_events.c player/minimap_system.c\
		player/fs_minimap_system.c cleanup/clean_and_exit.c
OBJSDIR = .build/

OBJS = $(patsubst %.c, $(OBJSDIR)%.o,$(SRCS))

TOTAL_SRCS := $(words $(SRCS))
COMPILED_SRCS := 0

.PHONY : all
all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT) $(MLX)
	@echo "\n$(COLOR_GREEN)Linking objects...$(COLOR_RESET)"
	@$(CC) $(OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS) $(MATHS_FLAGS) $(CFLAGS) -o $(NAME)
	@echo "$(COLOR_RED)$(NAME) compiled !$(COLOR_RESET)"

$(OBJSDIR)%.o : $(SRCSDIR)%.c $(HEADERS) $(LIBFT) $(MLX) | $(OBJSDIR)
	@mkdir -p $(dir $@)
	@$(eval COMPILED_SRCS=$(shell echo $$(($(COMPILED_SRCS)+1))))
	@printf "\rCompiling $(NAME): [%-50s] %d/%d " \
	"$(shell printf '#%.0s' $$(seq 1 $$(($(COMPILED_SRCS)*50/$(TOTAL_SRCS)))))" \
	$(COMPILED_SRCS) $(TOTAL_SRCS)
	@$(CC) -o $@ -c $< $(CFLAGS) $(INCFLAG)$(HEADERSDIR) $(INCFLAG)$(LIBFTINCDIR) $(INCFLAG)$(MLXDIR)

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