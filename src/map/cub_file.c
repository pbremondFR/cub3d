/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 22:27:10 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/29 10:54:45 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

// Using a double pointer here in case I want to overwrite previous texture
// instead of quitting program.
static void	_import_texture(t_img **dest_ptr, const char *line, t_game *g,
	bool cache_rot)
{
	t_img	*dest;

	dest = *dest_ptr;
	if (dest != NULL)
	{
		ft_dprintf(2, "Error\nRedefined `%c%c' texture.\n", *(line - 2),
			*(line - 1));
		c_exit_program(g, 1);
	}
	else
		*dest_ptr = c_import_xpm(line, g, cache_rot);
	if (*dest_ptr == NULL)
		c_exit_program(g, 1);
}

static int	_process_line(const char *line, t_cub *c, t_game *g)
{
	size_t	i;

	i = 0;
	while (ft_isspace(line[i]))
		++i;
	if (line[i] == '#')
		return (0);
	else if (ft_strncmp(line + i, "NO", 2) == 0)
		_import_texture(&c->n, line + i + 2, g, true);
	else if (ft_strncmp(line + i, "SO", 2) == 0)
		_import_texture(&c->s, line + i + 2, g, true);
	else if (ft_strncmp(line + i, "EA", 2) == 0)
		_import_texture(&c->e, line + i + 2, g, true);
	else if (ft_strncmp(line + i, "WE", 2) == 0)
		_import_texture(&c->w, line + i + 2, g, true);
	else if (line[i] == 'F')
		c->f = c_parse_color(line + i + 1, c->f);
	else if (line[i] == 'C')
		c->c = c_parse_color(line + i + 1, c->c);
	else if (line[i] != '\0' && ft_strchr("01NESW", line[i]))
		return (1);
	return (0);
}

static int	_missing_elements_check(const t_cub *c)
{
	const t_img	*textures[] = {c->n, c->s, c->w, c->e};
	const char	*names[] = {"North", "South", "West", "East"};
	int			i;

	i = -1;
	while (++i < 4)
	{
		if (textures[i] == NULL)
		{
			ft_dprintf(2, "Error\nMissing %s texture\n", names[i]);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

// Could also use autovar from main's stack ?
// NOTE: Don't get confused by first use of *line. It's just to save space.
t_cub	*c_parse_cub_file(const char *path, t_cub *c, t_game *g)
{
	const char	*line;
	int			fd;

	fd = c_cub_try_open_file(path);
	c_init_t_cub(c);
	line = get_next_line(fd);
	while (line)
	{
		if (_process_line(line, c, g) == 1)
			c_parse_map(line, fd, c);
		ft_strrep((char **)&line, get_next_line(fd));
	}
	if (_missing_elements_check(c) != EXIT_SUCCESS)
		return (NULL);
	return (c);
}
