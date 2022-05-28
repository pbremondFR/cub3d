/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_graphics.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:15:10 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/28 02:40:42 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

#define REDEF_COLOUR	1
#define MISS_RGB_COMP	2
#define ILLEGAL_RANGE	3

static int	_color_error(int code)
{
	if (code == REDEF_COLOUR)
		ft_dprintf(2, "Error\nRedefined colour\n");
	if (code == MISS_RGB_COMP)
		ft_dprintf(2, "Error\nMissing RGB component or incorrect format\n");
	else if (code == ILLEGAL_RANGE)
		ft_dprintf(2, "Error\nRGB components must be in range [0-255]\n");
	return (-2);
}

// Returns an int representing a color in RGB format, in range [0x00 - 0xff]
// Outputs an error message and returns -1 if error is found.
int	c_parse_color(const char *line, int old_colour)
{
	const char	*begin;
	int			i;
	int			num;
	int			color;

	if (old_colour != -1)
		return (_color_error(REDEF_COLOUR));
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
	char	**dump_tab;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_dprintf(2, "Error\nCouldn't open %s: %s\n", path, strerror(errno));
		return (NULL);
	}
	line = get_next_line(fd);
	filedump = ft_strnew(0);
	while (line)
	{
		filedump = ft_stradd2(filedump, line, 3);
		line = get_next_line(fd);
	}
	dump_tab = ft_split(filedump, '\n');
	free(filedump);
	return (dump_tab);
}

// TODO: Check if file exists and can be opened
t_img	*c_import_xpm(const char *path, t_game *g, bool opt)
{
	char	*trimmed;
	t_img	*img;

	trimmed = ft_strtrim(path, " \t\n\v\f\r");
	img = (t_img *)malloc(sizeof(t_img));
	if (img == NULL)
		return (NULL);
	img->i = mlx_xpm_file_to_image(g->mlx, trimmed, &img->w, &img->h);
	if (img->i == NULL)
	{
		ft_dprintf(2, "Error\nCouldn't import `%s' texture.\n", trimmed);
		return (NULL);
	}
	if (opt == true && img->w != img->h)
	{
		ft_dprintf(2, "Error\nTexture in `%s' is not squared.\n", trimmed);
		mlx_destroy_image(g->mlx, img->i);
		return (NULL);
	}
	free(trimmed);
	img->addr = mlx_get_data_addr(img->i, &img->bpp, &img->ls, &img->e);
	if (opt == true && c_opt_texture_for_cache(img) != EXIT_SUCCESS)
		return (NULL);
	return (img);
}
