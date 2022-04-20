/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 08:26:34 by pbremond          #+#    #+#             */
/*   Updated: 2022/04/20 11:47:51 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <libft.h>

void	c_ray_calc_step_and_len(t_ray *ray, float pos_x, float pos_y)
{
	if (ray->dir_x < 0.0f)
	{
		ray->step_x = -1;
		ray->len_x = (pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->len_x = (ray->map_x + 1.0f - pos_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0.0f)
	{
		ray->step_y = -1;
		ray->len_y = (pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->len_y = (ray->map_y + 1.0f - pos_y) * ray->delta_dist_y;
	}
}

void	c_ray_raycasting_loop(t_game *g, t_ray *ray)
{
	while (1)
	{
		if (ray->map_x < 0 || (t_uint)ray->map_x > g->c->sx
			|| ray->map_y < 0 || (t_uint)ray->map_y > g->c->sy
			|| g->c->map[ray->map_y][ray->map_x] == '1')
			break ;
		if (ray->len_x < ray->len_y)
		{
			ray->len_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->len_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
	}
}
