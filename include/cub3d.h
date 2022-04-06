/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 20:43:01 by pbremond          #+#    #+#             */
/*   Updated: 2022/04/06 16:01:37 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include <math.h>

# include "ansi_color.h"
# include "mlx.h"

# define MAP_LEGAL_CHARS	"01NESW \t\n\v\f\r"
# define M_CHRS				MAP_LEGAL_CHARS

# define MLX_BETA

# define EVENT_KEY_DOWN			2
# define EVENT_KEY_UP			3
# define EVENT_SCROLL_DOWN		4
# define EVENT_SCROLL_UP		5
# define EVENT_MOUSE_MOVE		6
# define EVENT_EXPOSE			12
# define EVENT_DESTROY			17

# define E_KDWN		EVENT_KEY_DOWN
# define E_KUP		EVENT_KEY_UP
# define E_MDWN		EVENT_SCROLL_DOWN
# define E_MUP		EVENT_SCROLL_UP
# define E_MMOV		EVENT_MOUSE_MOVE
# define E_XP		EVENT_EXPOSE
# define E_DSTR		EVENT_DESTROY

# define MLX_SYNC_IMAGE_WRITABLE	1
# define MLX_SYNC_WIN_FLUSH_CMD		2
# define MLX_SYNC_WIN_CMD_COMPLETED	3

# define KEYC_ESC	53
# define KEYC_W		13
# define KEYC_A		0
# define KEYC_S		1
# define KEYC_D		2

# define KEYS_ESC	0b10000000
# define KEYS_W		0b00001000
# define KEYS_A		0b00000001
# define KEYS_S		0b00000010
# define KEYS_D		0b00000100

# define WIN_WIDTH		1920
# define WIN_HEIGHT		540
# define WIN_FWIDTH		1920.0f
# define WIN_FHEIGHT	540.0f

# define ACCEL		1.0f
# define DECEL		0.5f
# define MAX_VEL	10.0f

typedef struct s_cub_data
{
	char	**map;
	char	**n; // North xpm
	char	**s; // South xpm
	char	**e; // East xpm
	char	**w; // West xpm

	int		f; // Floor
	int		c; // Ceiling
}				t_cub;

typedef struct s_mlx_img
{
	void	*i; // Image handle
	char	*addr; // Char buffer to write into

	int		bpp; // Bits per pixel
	int		ls; // Line size
	int		e; // Endian
}				t_img;

typedef struct s_game_data
{
	float	x; // Player x position
	float	y; // Player y position
	float	dx; // Player direction vector's x
	float	dy; // Player direction vector's y
	float	vx; // Player x velocity
	float	vy; // Player y velocity

	char	k; // Keystate

	void	*mlx; // MLX handle
	void	*mw; // MLX window
	t_img	i; // MLX image

	t_cub	*c; // .cub file data
}				t_game;

t_cub	*c_init_t_cub(t_cub *p_cub);

int		str_isspace(const char *line);
t_cub	*c_parse_cub_file(const char *path, t_cub *c);
void	c_parse_map(const char *first_line, int fd, t_cub *c);
int		c_map_error_check(const char **map);
int		c_is_flooradj_legal(const char c);
void	c_map_print_error(const char **map, unsigned int x, unsigned int y);

char	**c_import_xpm(const char *line);
int		c_parse_color(const char *line);

size_t	ft_stmin(size_t a, size_t b);

void	c_move_player(t_game *g);
int		c_render(void *handle);
int		c_keypress_handler(int key, void *handle);
int		c_keyrelease_handler(int key, void *handle);

void	my_mlx_pixel_put(struct s_mlx_img *img, int x, int y, int color);

#endif
