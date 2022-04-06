/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:42:48 by pbremond          #+#    #+#             */
/*   Updated: 2022/04/06 16:43:19 by pbremond         ###   ########.fr       */
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
