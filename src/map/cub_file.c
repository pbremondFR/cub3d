/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 22:27:10 by pbremond          #+#    #+#             */
/*   Updated: 2022/04/21 13:46:29 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

// Initializes all members of t_cub. If p_cub is NULL, mallocs a t_cub and
// returns it.
t_cub	*c_init_t_cub(t_cub *p_cub)
{
	t_cub	*cub;

	if (p_cub)
		cub = p_cub;
	else
		cub = (t_cub *)malloc(sizeof(t_cub));
	cub->map = NULL;
	cub->sx = 0;
	cub->sy = 0;
	cub->n = NULL;
	cub->s = NULL;
	cub->e = NULL;
	cub->w = NULL;
	cub->f = -1;
	cub->c = -1;
	return (cub);
}

// FIXME: Will leak if a texture is redefined in file
static int	_process_line(const char *line, t_cub *c, t_game *g)
{
	size_t	i;

	i = 0;
	while (ft_isspace(line[i]))
		++i;
	if (ft_strncmp(line + i, "NO", 2) == 0)
		c->n = c_import_xpm(line + i + 2, g);
	else if (ft_strncmp(line + i, "SO", 2) == 0)
		c->s = c_import_xpm(line + i + 2, g);
	else if (ft_strncmp(line + i, "EA", 2) == 0)
		c->e = c_import_xpm(line + i + 2, g);
	else if (ft_strncmp(line + i, "WE", 2) == 0)
		c->w = c_import_xpm(line + i + 2, g);
	else if (ft_strncmp(line + i, "F", 1) == 0)
		c->f = c_parse_color(line + i + 1);
	else if (ft_strncmp(line + i, "C", 1) == 0)
		c->c = c_parse_color(line + i + 1);
	else if (ft_strchr("01NESW", line[i]))
		return (1);
	return (0);
}

// Could also use autovar from main's stack ?
// NOTE: Don't get confused by first use of *line. It's just to save space.
t_cub	*c_parse_cub_file(const char *path, t_cub *c, t_game *g)
{
	const char	*line;
	int			fd;

	line = path + (ft_strlen(path) - ft_stmin(ft_strlen(path), 4));
	if (ft_strncmp(line, ".cub", 4) != 0)
	{
		ft_dprintf(2, "Error\nExpected `*.cub' file, got `%s'\n", path);
		return (NULL);
	}
	c_init_t_cub(c);
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_dprintf(2, "Error\nCouldn't open %s: %s\n", path, strerror(errno));
		return (NULL);
	}
	line = get_next_line(fd);
	while (line)
	{
		if (_process_line(line, c, g) == 1)
			c_parse_map(line, fd, c);
		ft_strrep((char **)&line, get_next_line(fd));
	}
	return (c);
}
