# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/25 15:25:19 by pbremond          #+#    #+#              #
#    Updated: 2023/01/16 19:51:59 by pbremond         ###   ########.fr        #
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
OBJ_DIR = objs

# ============================================================================ #
# ============================================================================ #

# Common source files
SRC_COMMON =	$(MAP_SRC) $(RENDER_SRC)\
				input/keyboard.c\
				input/mouse.c\
				utils.c\
				maths/math_funcs.c\
				collisions/collision_detection.c

MAP_SRC_FILES =			cub_graphics.c		map_parsing.c		map_parsing_2.c\
	checking_funcs.c	map_print.c			cub_graphics_2.c\
	cub_file_utils.c

RENDER_SRC_FILES =		utils.c				movement.c\
	textures.c			textures_2.c

MAP_SRC =		$(addprefix map/,		$(MAP_SRC_FILES))
RENDER_SRC =	$(addprefix render/,	$(RENDER_SRC_FILES))

# ============================================================================ #
# ============================================================================ #

SRC_MANDATORY =	$(SRC_COMMON)\
				main.c\
				render/rendering.c\
				map/map_error_check.c\
				map/cub_file.c\
				raycast/raycast.c\
				collisions/collision_detection_utils.c

SRC_MANDATORY_PLUS_PATH = $(addprefix $(SRC_DIR)/, $(SRC_MANDATORY))
OBJ = $(subst $(SRC_DIR)/, $(OBJ_DIR)/, $(patsubst %.c, %.o, $(SRC_MANDATORY_PLUS_PATH)))

# ============================================================================ #
# ============================================================================ #

# Bonus source files
SRC_BONUS =	$(SRC_COMMON) $(RENDER_SRC_BONUS) $(MAP_SRC_BONUS)\
			main_bonus.c\
			str_display/font_display_bonus.c\
			str_display/font_display_bonus_2.c\
			minimap/minimap_bonus.c\
			minimap/minimap_bonus_2.c\
			raycast/raycast_bonus.c\
			utils_bonus.c\
			collisions/collision_detection_utils_bonus.c

RENDER_SRC_FILES_BONUS =	rendering_bonus.c			sprites_bonus.c\
	sprites_utils_bonus.c	sprites_sorting_bonus.c		sprite_barrel_bonus.c\
	doors_bonus.c

MAP_SRC_FILES_BONUS =		cub_file_bonus.c		cub_graphics_sprites_bonus.c\
	map_parsing_bonus.c	map_error_check_bonus.c

RENDER_SRC_BONUS =	$(addprefix render/,	$(RENDER_SRC_FILES_BONUS))
MAP_SRC_BONUS =		$(addprefix map/,		$(MAP_SRC_FILES_BONUS))

SRC_BONUS_PLUS_PATH = $(addprefix $(SRC_DIR)/, $(SRC_BONUS))
BONUS_OBJ = $(subst $(SRC_DIR)/, $(OBJ_DIR)/, $(patsubst %.c, %.o, $(SRC_BONUS_PLUS_PATH)))

# ============================================================================ #
# ============================================================================ #

LIBFT = libft.a
LIBFT_PATH = libft
LIBMLX = libmlx.a
LIBMLX_PATH = mlx_opengl
### Commented out for public push without libft
# LIBS = -L./libft -lft -L./mlx_opengl -lmlx -framework OpenGL -framework AppKit
LIBS = -L. -lft -L./mlx_opengl -lmlx -framework OpenGL -framework AppKit

NAME = cub3d
NAME_BONUS = cub3d_bonus

CC = clang
CFLAGS = -Wall -Wextra -Werror -O2 #-g #-fsanitize=address

all : $(NAME_BONUS)

### Commented out for public push without libft
# $(NAME): $(LIBFT_PATH)/$(LIBFT) $(LIBMLX_PATH)/$(LIBMLX) $(OBJ)
# 	@echo "$(_PURPLE)Linking $(NAME)$(_COLOR_RESET)"
# 	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)
# 	@echo "$(_GREEN)DONE$(_COLOR_RESET)"

$(NAME): $(LIBMLX_PATH)/$(LIBMLX) $(OBJ)
	@echo "$(_PURPLE)Linking $(NAME)$(_COLOR_RESET)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)
	@echo "$(_GREEN)DONE$(_COLOR_RESET)"

bonus: $(NAME_BONUS)

### Commented out for public push without libft
# $(NAME_BONUS): $(LIBFT_PATH)/$(LIBFT) $(LIBMLX_PATH)/$(LIBMLX) $(BONUS_OBJ)
# 	@echo "$(_PURPLE)Linking $(NAME_BONUS)$(_COLOR_RESET)"
# 	@$(CC) $(CFLAGS) $(BONUS_OBJ) -o $(NAME_BONUS) $(LIBS)
# 	@echo "$(_GREEN)DONE$(_COLOR_RESET)"

$(NAME_BONUS): $(LIBMLX_PATH)/$(LIBMLX) $(BONUS_OBJ)
	@echo "$(_PURPLE)Linking $(NAME_BONUS)$(_COLOR_RESET)"
	@$(CC) $(CFLAGS) $(BONUS_OBJ) -o $(NAME_BONUS) $(LIBS)
	@echo "$(_GREEN)DONE$(_COLOR_RESET)"

### Commented out for public push without libft
# $(LIBFT_PATH)/$(LIBFT):
# 	@echo "$(_PURPLE)Making $(basename $(LIBFT))$(_COLOR_RESET)"
# 	@make -C $(LIBFT_PATH)

$(LIBMLX_PATH)/$(LIBMLX):
	@echo "$(_PURPLE)Making $(basename $(LIBMLX))$(_COLOR_RESET)"
	@make -C $(LIBMLX_PATH)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@echo "$(_BLUE)Compiling $(basename $(notdir $*.o)) $(_COLOR_RESET)"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@ -I./$(INCLUDES)


re: fclean all

rebonus: fclean bonus

b: bonus

fclean: clean
	@echo "$(_RED)Deleting $(NAME) & $(NAME_BONUS)$(_COLOR_RESET)"
	@rm -rf $(NAME) $(NAME_BONUS)

clean:
	@echo "$(_RED)Cleaning object files$(_COLOR_RESET)"
	@rm -rf $(OBJ_DIR)
	
.PHONY: clean fclean re all bonus debug
