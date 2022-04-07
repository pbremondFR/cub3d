# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/25 15:25:19 by pbremond          #+#    #+#              #
#    Updated: 2022/04/07 14:30:57 by pbremond         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
_BLACK			= \033[0;30m
_RED 			= \033[0;31m
_GREEN			= \033[0;32m
_BROWN			= \033[0;33m
_BLUE			= \033[0;34m
_PURPLE			= \033[0;35m
_CYAN			= \033[0;36m
_LIGHT_GRAY		= \033[0;37m
_DARK_GRAY		= \033[1;30m
_LIGHT_RED		= \033[1;31m
_LIGHT_GREEN	= \033[1;32m
_YELLOW			= \033[1;33m
_LIGHT_BLUE		= \033[1;34m
_LIGHT_PURPLE	= \033[1;35m
_LIGHT_CYAN		= \033[1;36m
_WHITE			= \033[1;37m
_NC 			= \033[0m

# Inverted, i.e. colored backgrounds
_IGREY			= \x1b[40m
_IRED			= \x1b[41m
_IGREEN			= \x1b[42m
_IYELLOW		= \x1b[43m
_IBLUE			= \x1b[44m
_IPURPLE		= \x1b[45
_ICYAN			= \x1b[46m
_IWHITE			= \x1b[47m

# Color reset
_COLOR_RESET	= \033[0m

# Folders
INCLUDES = include
SRC_DIR = src
OUTS = objs

# Source Files
SRC =	$(MAP_SRC) $(RENDER_SRC)\
		main.c\
		keyboard.c\
		maths/math_funcs.c

MAP_SRC_FILES =			cub_file.c		cub_graphics.c		map_parsing.c\
	checking_funcs.c	map_print.c

RENDER_SRC_FILES =		something.c		utils.c				movement.c

MAP_SRC =		$(addprefix map/,		$(MAP_SRC_FILES))
RENDER_SRC =	$(addprefix render/,	$(RENDER_SRC_FILES))
		
SRC_PLUS_PATH = $(addprefix $(SRC_DIR)/, $(SRC))

# Output Files
OUT = $(subst $(SRC_DIR)/, $(OUTS)/, $(patsubst %.c, %.o, $(SRC_PLUS_PATH)))

# BONUS_SRCS = main_bonus.c

# This project requires the libreadline library to be installed! Either get it
# via homebrew, or include your own custom install down below.
LIBFT = libft.a
LIBFT_PATH = libft
LIBMLX_PATH = mlx_beta
LIBS = -framework OpenGL -framework AppKit

NAME = cub3d

CC = clang
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

all : $(NAME)

$(NAME): $(LIBFT_PATH)/$(LIBFT) $(OUT)
	@echo "$(_PURPLE)Linking $(NAME)$(_COLOR_RESET)"
	@$(CC) $(CFLAGS) $(OUT) -o $(NAME) -L./libft -lft -L./mlx_beta -lmlx $(LIBS)
	@echo "$(_GREEN)DONE$(_COLOR_RESET)"

$(LIBFT_PATH)/$(LIBFT):
	@echo "$(_PURPLE)Making $(basename $(LIBFT))$(_COLOR_RESET)"
	@make -C $(LIBFT_PATH)/

$(OUT): $(OUTS)/%.o : $(SRC_DIR)/%.c
	@echo "$(_BLUE)Compiling $(basename $(notdir $*.o)) $(_COLOR_RESET)"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@ -I./$(INCLUDES)

re: fclean $(NAME)

fclean: clean
	@echo "$(_RED)Cleaning output files$(_COLOR_RESET)"
	@rm -rf $(NAME)

clean:
	@echo "$(_RED)Cleaning object files$(_COLOR_RESET)"
	@rm -rf $(OUTS)
	
.PHONY: clean fclean re all
