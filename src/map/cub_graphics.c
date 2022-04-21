/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_graphics.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:15:10 by pbremond          #+#    #+#             */
/*   Updated: 2022/04/21 13:50:55 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

#define MISS_RGB_COMP	1
#define ILLEGAL_RANGE	2

static int	_color_error(int code)
{
	if (code == MISS_RGB_COMP)
		ft_dprintf(2, "Error\nMissing RGB component or incorrect format\n");
	else if (code == ILLEGAL_RANGE)
		ft_dprintf(2, "Error\nRGB components must be in range [0-255]\n");
	return (-1);
}

// Returns an int representing a color in RGB format, in range [0x00 - 0xff]
// Outputs an error message and returns -1 if error is found.
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
			return (_color_error(MISS_RGB_COMP));
		num = ft_atoi(begin);
		if (num > 0xff || num < 0x00)
			return (_color_error(ILLEGAL_RANGE));
		color |= num << (8 * i--);
		begin = ++line;
	}
	return (color);
}

char	**c_xpm_to_char(const char *path)
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

static int	_get_2darr_size(const char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		++i;
	return (i);
}

// Returns a char 2D array which is a dump of given XPM file.
t_img	*c_import_xpm(const char *path, t_game *g)
{
	char	*trimmed;
	char	**xpm_dump;
	t_img	*img;

	trimmed = ft_strtrim(path, " \t\n\v\f\r");
	xpm_dump = c_xpm_to_char(trimmed);
	free(trimmed);
	img = (t_img *)malloc(sizeof(t_img));
	if (img == NULL)
		return (NULL);
	img->i = mlx_xpm_to_image(g->mlx, xpm_dump, &img->w, &img->h);
	ft_split_free(xpm_dump, _get_2darr_size((const char **)xpm_dump));
	if (img->i == NULL)
		return (NULL);
	img->addr = mlx_get_data_addr(img->i, &img->bpp, &img->ls, &img->e);
	return (img);
}
