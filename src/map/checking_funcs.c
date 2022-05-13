/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:44:26 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/13 16:27:23 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

// Checks if given char has the right to be adjacent to a floor tile
int	c_is_flooradj_legal(const char c)
{
	if (c == '\0')
		return (0);
	if (!ft_strchr(LEGAL_FLOOR_NEIGHBOURS, c))
		return (0);
	return (1);
}

int	str_isspace(const char *line)
{
	while (*line)
	{
		if (!ft_isspace(*line))
			return (0);
		line++;
	}
	return (1);
}

size_t	ft_stmin(size_t a, size_t b)
{
	if (a < b)
		return (a);
	return (b);
}
