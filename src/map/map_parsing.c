/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 20:42:12 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/06 22:09:01 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

// Finds trailing whitespaces in each map line, and simply replaces them with
// '\0'. Does not reallocate anything!
static void	_remove_trailing_spaces(char *line)
{
	size_t	i;

	i = ft_strlen(line);
	while (i > 0 && ft_isspace(line[i]))
		--i;
	ft_memset(line + i, '\0', ft_strlen(line) - i);
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
		line = get_next_line(fd);
	}
	c->map = ft_split(map, '\n');
	free(map);
	i = 0;
	while (c->map[i])
	{
		_remove_trailing_spaces(c->map[i]);
		if (c->sx < ft_strlen(c->map[i++]))
			c->sx = ft_strlen(c->map[i - 1]);
	}
	c->sy = i;
	_align_map_line_lengths(c);
}

// TESTME: What to do when changing FOV, or aspect ratio of window ?
static void	_set_player_direction(char *c, t_game *g)
{
	const float	fov = PLAYER_FOV;

	if (*c == 'N' || *c == 'S')
	{
		g->dx = 0.0f;
		if (*c == 'N')
			g->dy = -1.0f;
		else
			g->dy = 1.0f;
		g->cx = -g->dy * fov;
		g->cy = g->dx;
	}
	else if (*c == 'E' || *c == 'W')
	{
		if (*c == 'E')
			g->dx = 1.0f;
		else
			g->dx = -1.0f;
		g->dy = 0.0f;
		g->cx = -g->dy;
		g->cy = g->dx * fov;
	}
	*c = '0';
}

void	c_init_player_pos(t_game *g, t_cub *c)
{
	int	i;
	int	j;

	g->x = 0.0f;
	g->y = 0.0f;
	i = -1;
	while (c->map[++i])
	{
		j = -1;
		while (c->map[i][++j])
		{
			if (ft_strchr("NESW", c->map[i][j]) && g->x == 0.0f && g->y == 0.0f)
			{
				g->x = j + 0.5f;
				g->y = i + 0.5f;
				_set_player_direction(&c->map[i][j], g);
			}
			else if (ft_strchr("NESW", c->map[i][j]))
			{
				ft_dprintf(2, "Error\nPlayer position set more than once\n");
				c_map_print_error((const char **)c->map, j, i);
				c_exit_program(g);
			}
		}
	}
}
