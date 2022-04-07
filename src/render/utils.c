/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:42:48 by pbremond          #+#    #+#             */
/*   Updated: 2022/04/07 17:03:50 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

// Imma steal that for now
void	my_mlx_pixel_put(struct s_mlx_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->ls + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_square(struct s_mlx_img *img, int x, int y, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < PLY_HITBX_SIZ)
	{
		j = -1;
		while (++j < PLY_HITBX_SIZ)
			my_mlx_pixel_put(img, x + j, y + i, color);
	}
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

void	c_draw_vision(t_game *g, t_uint len, int color1, int color2)
{
	t_pnt	a;
	t_pnt	b;

	a.x = g->x * MAP_TILE_SIZE;
	a.y = g->y * MAP_TILE_SIZE;
	b.x = a.x + g->dx * len;
	b.y = a.y + g->dy * len;
	if (b.x < 0.0f)
		b.x = 0.0f;
	else if (b.x > WIN_FWIDTH)
		b.x = WIN_FWIDTH;
	if (b.y < 0.0f)
		b.y = 0.0f;
	else if (b.y > WIN_FHEIGHT)
		b.y = WIN_FHEIGHT;
	c_draw_line(&g->i, a, b, color1);
	a.x = b.x + g->cx * len;
	a.y = b.y + g->cy * len;
	if (a.x < 0.0f)
		a.x = 0.0f;
	else if (a.x > WIN_FWIDTH)
		a.x = WIN_FWIDTH;
	if (a.y < 0.0f)
		a.y = 0.0f;
	else if (a.y > WIN_FHEIGHT)
		a.y = WIN_FHEIGHT;
	c_draw_line(&g->i, a, b, color2);
}
