/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 20:43:01 by pbremond          #+#    #+#             */
/*   Updated: 2022/04/05 20:11:10 by pbremond         ###   ########.fr       */
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

# include "ansi_color.h"
# include <mlx.h>

# define MAP_LEGAL_CHARS	"01NESW \t\n\v\f\r"
# define M_CHRS				MAP_LEGAL_CHARS

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

typedef struct s_game_data
{
	float	x; // Player x position
	float	y; // Player y position
	float	dx; // Player direction vector's x
	float	dy; // Player direction vector's y
	float	vx; // Player x velocity
	float	vy; // Player y velocity

	void	*mlx; // MLX handle
	void	*mw; // MLX window
	
	t_cub	*c; // .cub file data
}				t_game;

t_cub	*c_init_t_cub(t_cub *p_cub);

int		str_isspace(const char *line);
t_cub	*c_parse_cub_file(const char *path);
void	c_parse_map(const char *first_line, int fd, t_cub *c);
int		c_map_error_check(const char **map);
int		c_is_flooradj_legal(const char c);
void	c_map_print_error(const char **map, unsigned int x, unsigned int y);

char	**c_import_xpm(const char *line);
int		c_parse_color(const char *line);

size_t	ft_stmin(size_t a, size_t b);

#endif
