NAME = mapgen

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP
RM = rm -rf

LIBFTDIR = ../42Libft/
LIBFTINCDIR = $(LIBFTDIR)includes
PARSINGINCDIR = ../includes
LIBFT = $(LIBFTDIR)libft.a

HEADERSDIR = includes/
HEADERS = $(HEADERSDIR)mapgen.h

UTILSDIR = utils/
SRCSDIR = src/
SRCS = main.c \
		utils/border_walls.c utils/convert_args.c \
		utils/free_split.c utils/ft_rand.c \
		utils/init_config.c utils/print_map.c \
		utils/read_int_from_stdin.c \
		utils/update_player_dir.c utils/write_error.c \
		gnl_noleak/get_next_line.c gnl_noleak/get_next_line_utils.c 

OBJSDIR = .build/
OBJS = $(patsubst %.c, $(OBJSDIR)%.o,$(SRCS))
DEP = $(OBJS:.o=.d)



all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) Makefile
	$(CC) $(OBJS) $(CFLAGS) $(LIBFT) -o $(NAME) 

$(OBJSDIR)%.o: $(SRCSDIR)%.c $(HEADERS) | $(OBJSDIR)
	@mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(CFLAGS) -I$(LIBFTINCDIR) -I$(HEADERSDIR) -I$(PARSINGINCDIR)

$(OBJSDIR):
	@mkdir -p $(OBJSDIR)

$(LIBFT):
	@make -j -sC $(LIBFTDIR)

clean: 
	$(RM) $(OBJSDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re all

-include $(DEP)