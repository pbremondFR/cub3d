/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 08:26:34 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/18 20:44:11 by pbremond         ###   ########.fr       */
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

static bool	_ray_intersect(t_game *g, t_ray *ray)
{
	const char	tile = g->c->map[ray->map_y][ray->map_x];

	if (tile == '1')
		return (true);
	else if (tile == '|')
	{
		if (ray->len_x - ray->delta_dist_x / 2 < ray->len_y)
		{
			ray->len_x += ray->delta_dist_x / 2;
			ray->side = RAY_HIT_X;
			return (true);
		}
		else
			return (false);
	}
	else if (tile == '-')
	{
		float	test = g->x + (ray->len_y - ray->delta_dist_y / 2) * ray->dir_x;
		test -= (int)test;
		if (ray->len_x < ray->len_y - ray->delta_dist_y / 2)
			return (false);
		else if (test < 0.5f)
		{
			ray->len_y += ray->delta_dist_y / 2;
			ray->side = RAY_HIT_Y;
			return (true);
		}
		else
			return (false);
	}
	else
		return (false);
}

void	c_ray_raycasting_loop(t_game *g, t_ray *ray)
{
	while (1)
	{
		if (ray->map_x < 0 || (t_uint)ray->map_x >= g->c->sx
			|| ray->map_y < 0 || (t_uint)ray->map_y >= g->c->sy
			|| _ray_intersect(g, ray))
			break ;
		if (ray->len_x < ray->len_y)
		{
			ray->len_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = RAY_HIT_X;
		}
		else
		{
			ray->len_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = RAY_HIT_Y;
		}
	}
}
