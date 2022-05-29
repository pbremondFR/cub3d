/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 04:23:18 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/29 05:01:57 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <libft.h>

// Finds trailing whitespaces in each map line, and simply replaces them with
// '\0'. Does not reallocate anything!
static void	_remove_trailing_spaces(char *line)
{
	const size_t	old_len = ft_strlen(line);
	size_t			i;

	i = old_len - 1;
	while (i > 0 && ft_isspace(line[i]))
		--i;
	line[i + 1] = '\0';
}

static void	_align_map_line_lengths(t_cub *c)
{
	const t_uint	new_len = c->sx;
	t_uint			marker;
	char			*new_line;
	t_uint			i;

	i = 0;
	while (c->map[i])
	{
		new_line = (char *)malloc((new_len + 1) * sizeof(char));
		marker = ft_strlcpy(new_line, c->map[i], new_len + 1);
		ft_memset(new_line + marker, ' ', new_len - marker);
		new_line[new_len] = '\0';
		ft_strrep(&c->map[i], new_line);
		++i;
	}
}

void	c_parse_map_align_len(t_cub *c)
{
	int	i;

	i = -1;
	while (c->map[++i])
	{
		_remove_trailing_spaces(c->map[i]);
		if (c->sx < ft_strlen(c->map[i]))
			c->sx = ft_strlen(c->map[i]);
	}
	c->sy = i;
	_align_map_line_lengths(c);
}
