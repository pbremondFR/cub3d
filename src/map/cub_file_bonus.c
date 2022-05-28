/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_file_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 22:27:10 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/28 10:25:02 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d_bonus.h>

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
		c_exit_program(g);
	}
	else
		*dest_ptr = c_import_xpm(line, g, cache_rot);
	if (*dest_ptr == NULL)
		c_exit_program(g);
}

static int	_process_line(const char *line, t_cub *c, t_game *g)
{
	while (ft_isspace(*line))
		++line;
	if (*line == '#')
		return (0);
	else if (ft_strncmp(line, "NO", 2) == 0)
		_import_texture(&c->n, line + 2, g, true);
	else if (ft_strncmp(line, "SO", 2) == 0)
		_import_texture(&c->s, line + 2, g, true);
	else if (ft_strncmp(line, "EA", 2) == 0)
		_import_texture(&c->e, line + 2, g, true);
	else if (ft_strncmp(line, "WE", 2) == 0)
		_import_texture(&c->w, line + 2, g, true);
	else if (ft_strncmp(line, "DOOR", 4) == 0)
		_import_texture(&g->c->door, line + 4, g, true);
	else if (*line != '\0' && ft_strchr(SPRITE_IDS, *line))
		c_import_sprite(&c->sprt_src[*line - SPRITE_IDS[0]], line + 1, g);
	else if (*line == 'F')
		c->f = c_parse_color(line + 1, c->f);
	else if (*line == 'C')
		c->c = c_parse_color(line + 1, c->c);
	else if (*line != '\0' && ft_strchr("01NESW", *line))
		return (1);
	return (0);
}

// Yes, some of this is quite horrible, like that static i. It's just
// a cheap trick around the norm !
static int	_missing_texture_check(const t_cub *c)
{
	const t_img	*textures[] = {c->n, c->s, c->w, c->e, c->door};
	const char	*tex_names[] = {"North", "South", "West", "East", "Door"};
	const int	colours[] = {c->f, c->c};
	const char	*c_name[] = {"floor", "ceiling"};
	static int	i = -1;

	while (++i < 4)
	{
		if (textures[i] == NULL)
		{
			ft_dprintf(2, "Error\nMissing %s texture definition\n", tex_names[i]);
			return (EXIT_FAILURE);
		}
	}
	i = -1;
	while (++i < 2)
	{
		if (colours[i] == -1 || colours[i] == -2)
		{
			if (colours[i] == -1)
				ft_dprintf(2, "Error\nMissing %s colour definition\n", c_name[i]);
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
	if (fd == -1)
		return (NULL);
	c_init_t_cub(c);
	line = get_next_line(fd);
	while (line)
	{
		if (_process_line(line, c, g) == 1)
			c_parse_map(line, fd, c);
		ft_strrep((char **)&line, get_next_line(fd));
	}
	if (_missing_texture_check(c) != EXIT_SUCCESS)
		return (NULL);
	return (c);
}
