/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_graphics.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:15:10 by pbremond          #+#    #+#             */
/*   Updated: 2022/04/05 16:35:58 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

static int	_color_error(int code)
{
	if (code == 1)
		ft_dprintf(2, "Error\nMissing color or incorrect format\n");
	else if (code == 2)
		ft_dprintf(2, "Error\nColors must be in range [0-255]\n");
	return (-1);
}

int	c_parse_color(const char *line)
{
	const char	*begin;
	int			i;
	int			num;
	int			color;

	while (ft_isspace(*line))
		line++;
	begin = line;
	color = 0;
	i = 2;
	while (i >= 0 && *line)
	{
		while (*line && *line != ',')
			line++;
		if (i > 0 && *line == '\0')
			return (_color_error(1));
		num = ft_atoi(begin);
		if (num > 0xff || num < 0x00)
			return (_color_error(2));
		color |= num << (8 * i--);
		begin = ++line;
	}
	return (color);
}

static char	**c_xpm_to_char(const char *path)
{
	int		fd;
	char	*line;
	char	*filedump;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_dprintf(2, "Error\nCouldn't open %s: %s\n", path, strerror(errno));
		return (NULL);
	}
	line = get_next_line(fd);
	filedump = NULL;
	while (line)
	{
		filedump = ft_stradd2(filedump, line, 1 | 2);
		filedump = ft_stradd2(filedump, "\n", 1);
		line = get_next_line(fd);
	}
	return (ft_split(filedump, '\n'));
}

char	**c_import_xpm(const char *line)
{
	char	*trimmed;

	ft_printf("test\n");
	trimmed = ft_strtrim(line, " \t\n\v\f\r");
	return (c_xpm_to_char(trimmed));
}
