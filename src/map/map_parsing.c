/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 20:42:12 by pbremond          #+#    #+#             */
/*   Updated: 2022/04/04 16:17:06 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

// Finds trailing whitespaces in each map line, and simply replaces them with
// '\0'. Does not reallocate anything!
static void	remove_trailing_spaces(char *line)
{
	size_t	i;

	i = ft_strlen(line);
	while (i > 0 && ft_isspace(line[i]))
		--i;
	ft_memset(line + i, '\0', ft_strlen(line) - i);
}

void	c_parse_map(const char *first_line, int fd, t_cub *c)
{
	char	*map;
	char	*line;
	int		i;

	map = ft_strjoin(first_line, "\n");
	line = get_next_line(fd);
	while (line)
	{
		map = ft_stradd2(map, line, 1 | 2);
		map = ft_stradd2(map, "\n", 1);
		line = get_next_line(fd);
	}
	c->map = ft_split(map, '\n');
	i = 0;
	while (c->map[i])
		remove_trailing_spaces(c->map[i++]);
}

static int	check_map_is_last(const char **map)
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
static int	chk_tile_adj(const char **map, unsigned int x,
	unsigned int y)
{
	if (x == 0 || !c_is_flooradj_legal(map[y][x - 1])
		|| !c_is_flooradj_legal(map[y][x + 1]))
		return (EXIT_FAILURE);
	if (y == 0 || !c_is_flooradj_legal(map[y - 1][x])
		|| !c_is_flooradj_legal(map[y + 1][x]))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	c_map_error_check(const char **map)
{
	int	y;
	int	x;

	if (check_map_is_last(map) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if ((!ft_strchr(M_CHRS, map[y][x]))
				|| (map[y][x] == '0' && chk_tile_adj(map, x, y) != 0))
			{
				ft_dprintf(2, "Error\nIllegal map tile around (%d, %d)\n", x, y);
				c_map_print_error(map, x, y);
				return (EXIT_FAILURE);
			}
		}
	}
	return (EXIT_SUCCESS);
}
