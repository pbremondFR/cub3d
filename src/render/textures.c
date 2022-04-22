/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:04:49 by pbremond          #+#    #+#             */
/*   Updated: 2022/04/22 16:13:29 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

void	c_draw_wall_loop(t_game *g, const t_img *texture, int x, int height)
{
	const char	*addr = texture->addr;
	const int	oct_line_size = texture->ls >> 3;
	int			y_start;
	int			y_end;
	int			i;

	y_start = (-height >> 1) + (WIN_HEIGHT >> 1);
	if (y_start < 0)
		y_start = 0;
	y_end = (height / 2) + (WIN_HEIGHT / 2);
	if (y_end > WIN_HEIGHT - 1)
		y_end = WIN_HEIGHT - 1;
	i = 0;
	while (y_start + i < y_end)
	{
		
	}
}

void	c_start_draw_wall(t_game *g, t_ray *ray, int x)
{
	int		line_height;
	t_img	*texture_ptr;

	line_height = (int)(WIN_HEIGHT / ray->c_plane_len);
	if (ray->side == RAY_HIT_X && ray->dir_x > 0)
		texture_ptr = g->c->w;
	else if (ray->side == RAY_HIT_X && ray->dir_x < 0)
		texture_ptr = g->c->e;
	else if (ray->side == RAY_HIT_Y && ray->dir_y > 0)
		texture_ptr = g->c->s;
	else if (ray->side == RAY_HIT_Y && ray->dir_y > 0)
		texture_ptr = g->c->n;
	else
		texture_ptr = NULL; // TODO: Remove me when checking is done in .cub
}
