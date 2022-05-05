/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:55:04 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/05 15:33:51 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

void	c_map_print_error_old(const char **map, unsigned int x, unsigned int y)
{
	unsigned int	i;
	unsigned int	j;

	i = -1;
	while (map[++i])
	{
		if (i != y)
			ft_printf("%s\n", map[i]);
		else
		{
			j = -1;
			while (map[i][++j])
			{
				if (j == x)
					ft_putchar_clr(map[i][j], "\e[0;101m", 1);
				else
					ft_putchar(map[i][j]);
			}
			ft_putchar('\n');
		}
	}
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
			else if (map[i][j] == '0')
				ft_dprintf(2, "%s%c%s", BLK, map[i][j], RESET);
			else if (map[i][j] == '1')
				ft_dprintf(2, "%s%c%s", WHTB, map[i][j], RESET);
			else if (ft_strchr("NESW", map[i][j]))
				ft_dprintf(2, "%s%c%s", BLUB, map[i][j], RESET);
			else if (map[i][j] == ' ')
				ft_dprintf(2, "%s%c%s", YELB, map[i][j], RESET);
			else
				ft_dprintf(2, "%c", map[i][j]);
		}
		ft_putchar('\n');
	}
}
