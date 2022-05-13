/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:55:04 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/13 16:30:14 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

static void	_char_color_print(char c)
{
	if (c == '0')
		ft_dprintf(2, "%s%c%s", BLK, c, RESET);
	else if (c == '1')
		ft_dprintf(2, "%s%c%s", WHTB, c, RESET);
	else if (ft_strchr(SPRITE_IDS, c))
		ft_dprintf(2, "%s%c%s", GRNB, c, RESET);
	else if (ft_strchr("NESW", c))
		ft_dprintf(2, "%s%c%s", BLUB, c, RESET);
	else if (c == ' ')
		ft_dprintf(2, "%s%c%s", BLKB, c, RESET);
	else
		ft_putchar_fd(c, 2);
}

void	c_map_print_error(const char **map, unsigned int x, unsigned int y)
{
	unsigned int	i;
	unsigned int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (i == y && j == x)
				ft_dprintf(2, "%s%c%s", REDHB, map[i][j], RESET);
			else
				_char_color_print(map[i][j]);
		}
		ft_putchar_fd('\n', 2);
	}
}
