/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:42:48 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/12 01:57:03 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

// NOTE: This assumes that an int has the same number of bits as the image's
// bits per pixel, and uses the same endian. However, unless I were to try
// and port this to some obscure platform, it will be fine.
inline void	my_mlx_pixel_put(struct s_mlx_img *img, int x, int y, int color)
{
	*(int *)(img->addr + ((x * img->bpp >> 3) + (y * img->ls))) = color;
}

// Draws a simple line from point A to B on provided MLX image.
// NOTE: Does NOT protect against illegal memory access in image buffer.
// Double check A and B coordinates !
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

// Returns a pointer to pixel in MLX image at given coordinates.
char	*c_get_target_addr(t_img *i, int x, int y)
{
	x *= i->bpp >> 3;
	y *= i->ls;
	return (i->addr + x + y);
}

// Returns a pointer to pixel in MLX image at given coordinates.
const char	*c_get_const_target_addr(const t_img *i, int x, int y)
{
	x *= i->bpp >> 3;
	y *= i->ls;
	return (i->addr + x + y);
}

// void	c_draw_square(t_img *img, t_ipair coord, t_ipair colors, int size)
// {
// 	const int	int_line_size = img->ls >> 2;
// 	int			*img_buf;
// 	int			i;
// 	int			j;

// 	img_buf = (int *)(c_get_target_addr(img, coord.a, coord.b));
// 	j = 0;
// 	while (j < size)
// 		img_buf[j++] = colors.b;
// 	i = 1;
// 	while (i < size - 1)
// 	{
// 		img_buf[i * int_line_size] = colors.b;
// 		j = 1;
// 		while (j < size - 1)
// 			img_buf[i * int_line_size + j++] = colors.a;
// 		img_buf[i * int_line_size + j] = colors.b;
// 		++i;
// 	}
// 	j = 0;
// 	while (j < size)
// 		img_buf[i * int_line_size + j++] = colors.b;
// }

// Draws a square on given MLX image. Given coordinates represent the square's
// top left. The least significant 32 bits of `col' are the square's color.
// The most significant 32 bits are the square outline's color.
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
