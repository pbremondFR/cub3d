/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:42:48 by pbremond          #+#    #+#             */
/*   Updated: 2024/12/17 17:25:57 by pbremond         ###   ########.fr       */
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

double	timespec_difference(const struct timespec *a, const struct timespec *b)
{
	return ((a->tv_sec - b->tv_sec) + (a->tv_nsec - b->tv_nsec) / 1.0e9);
}
