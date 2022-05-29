/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 20:42:12 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/29 05:07:00 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

int	c_parse_map(const char *first_line, int fd, t_cub *c)
{
	char	*map;
	char	*line;
	size_t	old_len;

	map = ft_strjoin(first_line, "\n");
	line = get_next_line(fd);
	while (line)
	{
		if (old_len == 1 && ft_strlen(line) > 1)
		{
			free(map);
			free(line);
			ft_dprintf(2, "Error\nEmpty line in map\n");
			return (EXIT_FAILURE);
		}
		old_len = ft_strlen(line);
		map = ft_stradd2(map, line, 1 | 2);
		line = get_next_line(fd);
	}
	c->map = ft_split(map, '\n');
	free(map);
	c_parse_map_align_len(c);
	return (EXIT_SUCCESS);
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
				c_exit_program(g, 1);
			}
		}
	}
}
