/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 21:29:35 by pbremond          #+#    #+#             */
/*   Updated: 2023/01/16 19:44:39 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <assert.h>
#include <math.h>

static void	_sort_points_by_y(t_pnt *a, t_pnt *b, t_pnt *c)
{
	t_pnt	tmp;

	if (a->y > b->y)
	{
		tmp = *a;
		*a = *b;
		*b = tmp;
	}
	if (b->y > c->y)
	{
		tmp = *b;
		*b = *c;
		*c = tmp;
	}
	if (a->y > b->y)
	{
		tmp = *a;
		*a = *b;
		*b = tmp;
	}
}

void	draw_horiz_line(t_img *img, int x1, int x2, int y)
{
	int	tmp;

	if (x1 > x2)
	{
		tmp = x1;
		x1 = x2;
		x2 = tmp;
	}
	while (x1 <= x2)
	{
		*(int *)(img->addr + ((x1 * img->bpp >> 3) + (y * img->ls))) = 0xffffff;
		++x1;
	}
}

static void	_draw_bottom_flat_triangle(t_img *img, t_pnt a, t_pnt b, t_pnt c)
{
	const float	inv_slope_1 = (b.x - a.x) / (b.y - a.y);
	const float	inv_slope_2 = (c.x - a.x) / (c.y - a.y);
	float		current_x_1;
	float		current_x_2;
	int			line;

	current_x_1 = a.x;
	current_x_2 = a.x;
	line = a.y;
	while (line < b.y)
	{
		draw_horiz_line(img, (int)current_x_1, (int)current_x_2, line);
		current_x_1 += inv_slope_1;
		current_x_2 += inv_slope_2;
		line++;
	}
}

static void	_draw_top_flat_triangle(t_img *img, t_pnt a, t_pnt b, t_pnt c)
{
	const float	inv_slope_1 = (c.x - a.x) / (c.y - a.y);
	const float	inv_slope_2 = (c.x - b.x) / (c.y - b.y);
	float		current_x_1;
	float		current_x_2;
	int			line;

	current_x_1 = c.x;
	current_x_2 = c.x;
	line = c.y;
	while (line > a.y)
	{
		draw_horiz_line(img, (int)current_x_1, (int)current_x_2, line);
		current_x_1 -= inv_slope_1;
		current_x_2 -= inv_slope_2;
		line--;
	}
}

void	c_draw_triangle(t_img *img, t_pnt a, t_pnt b, t_pnt c)
{
	t_pnt	d;

	_sort_points_by_y(&a, &b, &c);
	assert(a.y <= b.y <= c.y);

	if ((int)b.y == (int)c.y)
		_draw_bottom_flat_triangle(img, a, b, c);
	else if ((int)a.y == (int)b.y)
		_draw_top_flat_triangle(img, a, b, c);
	else
	{
		d.x = (int)(a.x + ((b.y - a.y) / (c.y - a.y)) * (c.x - a.x));
		d.y = b.y;
		my_mlx_pixel_put(img, d.x, d.y, 0x0000ff);
		_draw_bottom_flat_triangle(img, a, b, d);
		_draw_top_flat_triangle(img, b, d, c);

		// c_draw_line(img, a, b, 0xff0000);
		// c_draw_line(img, b, d, 0xff0000);
		// c_draw_line(img, d, a, 0xff0000);

		// c_draw_line(img, b, d, 0xff0000);
		// c_draw_line(img, d, c, 0xff0000);
		// c_draw_line(img, c, b, 0xff0000);
	}
}
