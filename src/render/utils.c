/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:42:48 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/05 17:28:44 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

// Imma steal that for now
// Yes, it just assumes that img->bpp == 32 and thus isn't always portable.
// Too bad !
void	my_mlx_pixel_put(struct s_mlx_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->ls + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	c_draw_line(struct s_mlx_img *img, t_pnt a, t_pnt b, int color)
{
	float	dx;
	float	dy;
	t_pnt	p;
	float	step;
	t_uint	i;

	dx = b.x - a.x;
	dy = b.y - a.y;
	step = fabsf(dy);
	if (fabsf(dx) > fabsf(dy))
		step = fabsf(dx);
	dx = dx / step;
	dy = dy / step;
	i = 0;
	p.x = a.x;
	p.y = a.y;
	while (i++ <= step)
	{
		my_mlx_pixel_put(img, (int)p.x, (int)p.y, color);
		p.x += dx;
		p.y += dy;
	}
}

char	*c_get_target_addr(t_img *i, int x, int y)
{
	x *= i->bpp / 8;
	y *= i->ls;
	return (i->addr + x + y);
}

void	c_draw_square(t_img *img, t_ipair coord, t_ipair colors, int size)
{
	const int	int_line_size = img->ls >> 2;
	int			*img_buf;
	int			i;
	int			j;

	img_buf = (int *)(c_get_target_addr(img, coord.a, coord.b));
	j = 0;
	while (j < size)
		img_buf[j++] = colors.b;
	i = 1;
	while (i < size - 1)
	{
		img_buf[i * int_line_size] = colors.b;
		j = 1;
		while (j < size - 1)
			img_buf[i * int_line_size + j++] = colors.a;
		img_buf[i * int_line_size + j] = colors.b;
		++i;
	}
	j = 0;
	while (j < size)
		img_buf[i * int_line_size + j++] = colors.b;
}

void	c_draw_square_2(t_img *img, t_ipair coord, uint64_t col, int size)
{
	const int	int_line_size = img->ls >> 2;
	int			*img_buf;
	int			i;
	int			j;
	t_ipair		colors;

	colors.a = col & 0xffffffff;
	colors.b = col >> 32;
	img_buf = (int *)(c_get_target_addr(img, coord.a, coord.b));
	j = 0;
	while (j < size)
		img_buf[j++] = colors.b;
	i = 1;
	while (i < size - 1)
	{
		img_buf[i * int_line_size] = colors.b;
		j = 1;
		while (j < size - 1)
			img_buf[i * int_line_size + j++] = colors.a;
		img_buf[i * int_line_size + j] = colors.b;
		++i;
	}
	j = 0;
	while (j < size)
		img_buf[i * int_line_size + j++] = colors.b;
}
