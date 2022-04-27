/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:42:48 by pbremond          #+#    #+#             */
/*   Updated: 2022/04/27 21:38:14 by pbremond         ###   ########.fr       */
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
