# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/06 15:31:23 by tlutz             #+#    #+#              #
#    Updated: 2025/04/09 19:18:45 by tlutz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COLOR_GREEN = \033[0;32m
COLOR_RED = \033[0;31m
COLOR_YELLOW = \033[0;33m
COLOR_BLUE = \033[0;34m
COLOR_PURPLE = \033[0;35m
COLOR_CYAN = \033[0;36m
COLOR_RESET = \033[0m


INCFLAG = -I
CFLAGS = -Wall -Werror -Wextra
CC = cc

HEADERDIR = includes
HEADERS = includes/libft.h \
		includes/ft_printf.h \
		includes/get_next_line.h
		
SRCSDIR = srcs/
SRCS = converters/ft_atoi.c \
		mem_handling/ft_bzero.c \
		mem_handling/ft_calloc.c \
		char_checkers/ft_isalnum.c \
		char_checkers/ft_isalpha.c \
		char_checkers/ft_isascii.c \
		char_checkers/ft_isdigit.c \
		char_checkers/ft_isprint.c \
		converters/ft_itoa.c \
		mem_handling/ft_memchr.c \
		mem_handling/ft_memcmp.c \
		mem_handling/ft_memcpy.c \
		mem_handling/ft_memmove.c \
		mem_handling/ft_memset.c \
		writing/ft_putchar_fd.c \
		writing/ft_putendl_fd.c \
		writing/ft_putnbr_fd.c \
		writing/ft_putstr_fd.c \
		str_handling/ft_split.c \
		str_handling/ft_split_charset.c \
		str_handling/ft_strchr.c \
		str_handling/ft_strdup.c \
		str_handling/ft_strndup.c \
		str_handling/ft_striteri.c \
		str_handling/ft_strjoin.c \
		str_handling/ft_strcjoin.c \
		str_handling/ft_strlcat.c \
		str_handling/ft_strlcpy.c \
		str_handling/ft_strlen.c \
		str_handling/ft_strmapi.c \
		str_handling/ft_strncmp.c \
		str_handling/ft_strnstr.c \
		str_handling/ft_strrchr.c \
		str_handling/ft_strtrim.c \
		str_handling/ft_substr.c \
		str_handling/ft_strcmp.c \
		converters/ft_tolower.c \
		converters/ft_toupper.c \
		ft_printf/ft_printf.c \
		writing/ft_putptr.c \
		writing/ft_putnbr_base.c \
		writing/ft_uputnbr_base.c \
		writing/ft_wnumbers_base.c \
		gnl/get_next_line.c \
		chained_lists/ft_lstadd_front.c \
		chained_lists/ft_lstclear.c \
		chained_lists/ft_lstdelone.c \
		chained_lists/ft_lstlast.c \
		chained_lists/ft_lstnew.c \
		chained_lists/ft_lstsize.c \
		chained_lists/ft_lstadd_back.c \
		chained_lists/ft_lstiter.c \
		chained_lists/ft_lstmap.c
		
OBJSDIR = build/
OBJS = $(patsubst %.c,$(OBJSDIR)%.o,$(SRCS))

TOTAL_SRCS := $(words $(SRCS))
COMPILED_SRCS := 0

NAME = libft.a

all : $(NAME)

$(NAME) : $(OBJS)
	@echo "\n$(COLOR_GREEN)Linking objects...$(COLOR_RESET)"
	@ar rcs -o $(NAME) -c $(OBJS)
	@echo "$(COLOR_RED)$(NAME) created !$(COLOR_RESET)"

$(OBJSDIR)%.o : $(SRCSDIR)%.c $(HEADERS) | $(OBJSDIR)
	@mkdir -p $(dir $@)
	@$(eval COMPILED_SRCS=$(shell echo $$(($(COMPILED_SRCS)+1))))
	@printf "\rCompiling Libft: [%-50s] %d/%d" \
	"$(shell printf '#%.0s' $$(seq 1 $$(($(COMPILED_SRCS)*50/$(TOTAL_SRCS)))))" \
	$(COMPILED_SRCS) $(TOTAL_SRCS)
	@$(CC) $(INCFLAG)$(HEADERDIR) -o $@ -c $< $(CFLAGS)

$(OBJSDIR):
	@mkdir -p $(OBJSDIR)

clean :
	@echo "$(COLOR_BLUE)Cleaning objects...$(COLOR_RESET)"
	@rm -rf $(OBJSDIR)

fclean : clean
	@echo "$(COLOR_CYAN)Cleaning lib...$(COLOR_RESET)"
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
