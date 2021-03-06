/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error_check_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 21:28:36 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/29 11:57:54 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d_bonus.h>

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
static bool	_chk_tile_adj(const char **map, unsigned int x,
	unsigned int y)
{
	if (x == 0 || !c_is_flooradj_legal(map[y][x - 1])
		|| !c_is_flooradj_legal(map[y][x + 1]))
		return (false);
	if (y == 0 || !c_is_flooradj_legal(map[y - 1][x])
		|| !map[y + 1] || !c_is_flooradj_legal(map[y + 1][x]))
		return (false);
	return (true);
}

// Dear reader, I'm sorry.
static bool	_chk_door_adj(const char **map, unsigned int x,
	unsigned int y)
{
	const char	door = map[y][x];

	if (door == '-'
		&& (x == 0 || map[y][x - 1] != '1' || map[y][x + 1] != '1'
		|| y == 0 || !c_is_flooradj_legal(map[y - 1][x])
			|| !c_is_flooradj_legal(map[y + 1][x])))
		return (false);
	else if (door == '|'
		&& (y == 0 || map[y - 1][x] != '1' || !map[y + 1]
		|| map[y + 1][x] != '1' || x == 0
			|| !c_is_flooradj_legal(map[y][x - 1])
			|| !c_is_flooradj_legal(map[y][x + 1])))
		return (false);
	else
		return (true);
}

#define SPRT	SPRITE_IDS

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
				|| (ft_strchr("0"SPRT, map[y][x]) && !_chk_tile_adj(map, x, y))
				|| (ft_strchr("-|", map[y][x]) && !_chk_door_adj(map, x, y)))
			{
				ft_dprintf(2, "Error\nIllegal map tile around (%d, %d)\n", x, y);
				c_map_print_error(map, x, y);
				return (EXIT_FAILURE);
			}
		}
	}
	return (EXIT_SUCCESS);
}
