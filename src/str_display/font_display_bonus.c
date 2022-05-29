/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font_display_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:20:22 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/29 05:46:14 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d_bonus.h>

// bm_side_len.a = width / b = height
t_font	*c_parse_font_bitmap(t_game *g, char *path, t_ipair bm_side_len,
	int offset)
{
	t_font	*font;

	font = (t_font *)malloc(sizeof(t_font));
	if (font == NULL)
		return (NULL);
	font->i = mlx_xpm_file_to_image(g->mlx, path, &font->i_w, &font->i_h);
	if (font->i == NULL)
	{
		free(font);
		return (NULL);
	}
	font->addr = mlx_get_data_addr(font->i, &font->bpp, &font->ls, &font->e);
	font->bm_w = bm_side_len.a;
	font->bm_h = bm_side_len.b;
	font->offset = offset;
	font->c_w = font->i_w / font->bm_w;
	font->c_h = font->i_h / font->bm_h;
	return (font);
}

void	c_load_font(t_game *g)
{
	t_ipair	bm_side_len;

	bm_side_len.a = FONT_BM_W;
	bm_side_len.b = FONT_BM_H;
	g->c->font = c_parse_font_bitmap(g, FONT_PATH, bm_side_len, FONT_OFFSET);
}

const char	*_get_char_in_bitmap(const t_font *font, unsigned char c)
{
	t_uint		x;
	t_uint		y;

	c += font->offset;
	x = (c % font->bm_w) * font->c_w;
	y = (c / font->bm_w) * font->c_h;
	return (font->addr + ((y * font->ls) + (x * font->bpp / 8)));
}

void	_draw_font_line(int *dest, const int *src, t_uint len, int color)
{
	t_uint	i;
	int		src_color;

	i = 0;
	while (i < len)
	{
		src_color = src[i];
		if (src_color == 0xffffff)
			dest[i] = color;
		i++;
	}
}

// NOTE: A scaling factor here would have been cool... Although the norm
// won't allow it.
void	c_putstr_to_frame(t_game *g, t_ipair coord, int color, const char *str)
{
	int			i;
	int			j;
	const char	*c_addr;
	char		*target_addr;
	t_font		*font;

	font = g->c->font;
	i = -1;
	while (str[++i])
	{
		c_addr = _get_char_in_bitmap(font, str[i]);
		j = -1;
		while (++j < font->c_h)
		{
			target_addr = c_get_target_addr(&g->f, coord.a + i * font->c_w,
					coord.b + j);
			_draw_font_line((int *)target_addr,
				(const int *)(c_addr + j * font->ls), font->c_w, color);
		}
	}
}
