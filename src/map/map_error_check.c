/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 21:28:36 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/16 20:22:26 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

static int	_check_map_is_last(const char **map)
{
	int	y;

	y = -1;
	while (map[++y])
		if (ft_strlen(map[y]) == 0 || str_isspace(map[y]))
			break ;
	while (map[y])
	{
		if (ft_strlen(map[y]) != 0 && !str_isspace(map[y]))
		{
			ft_dprintf(2, "Error\nFound non-whitespace characters after map\n");
			return (EXIT_FAILURE);
		}
		y++;
	}
	return (EXIT_SUCCESS);
}

// Checks if a tile's neighbours in the 4 cardinal directions are legal.
static int	_chk_tile_adj(const char **map, unsigned int x,
	unsigned int y)
{
	if (x == 0 || !c_is_flooradj_legal(map[y][x - 1])
		|| !c_is_flooradj_legal(map[y][x + 1]))
		return (EXIT_FAILURE);
	if (y == 0 || !c_is_flooradj_legal(map[y - 1][x])
		|| !map[y + 1] || !c_is_flooradj_legal(map[y + 1][x]))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	c_map_error_check(const char **map)
{
	int	y;
	int	x;

	if (_check_map_is_last(map) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if ((!ft_strchr(M_CHRS, map[y][x]))
				|| (map[y][x] == '0' && _chk_tile_adj(map, x, y) != 0))
			{
				ft_dprintf(2, "Error\nIllegal map tile around (%d, %d)\n", x, y);
				c_map_print_error(map, x, y);
				return (EXIT_FAILURE);
			}
		}
	}
	return (EXIT_SUCCESS);
}
