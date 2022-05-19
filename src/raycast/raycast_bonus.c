/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 08:26:34 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/19 15:46:58 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>
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

// Actions to take with vertical door.
static bool	_vertical_door_intersect(t_game *g, t_ray *ray, int8_t *offset)
{
	const float	ray_y = g->y
		+ (ray->len_x - ray->delta_dist_x / 2) * ray->dir_y;
	const float	tex_pos = (ray_y - (int)ray_y) * 100;
	t_door		*door;

	door = c_get_door(g->c->doors, g->c->n_doors, ray->map_x, ray->map_y);
	if (door->state == DOOR_OPENED
		|| ray->len_y < ray->len_x - ray->delta_dist_x / 2)
		return (false);
	else if (door->state == DOOR_CLOSED
		|| (door->state != DOOR_CLOSED && tex_pos < door->open))
	{
		ray->len_x += ray->delta_dist_x / 2;
		ray->side = RAY_HIT_X;
		if (tex_pos < door->open)
			*offset = door->open;
		return (true);
	}
	return (false);
}

// Actions to take with horizontal door.
static bool	_horizontal_door_intersect(t_game *g, t_ray *ray, int8_t *offset)
{
	const float	ray_x = g->x
		+ (ray->len_y - ray->delta_dist_y / 2) * ray->dir_x;
	const float	tex_pos = (ray_x - (int)ray_x) * 100;
	t_door		*door;

	door = c_get_door(g->c->doors, g->c->n_doors, ray->map_x, ray->map_y);
	if (door->state == DOOR_OPENED
		|| ray->len_x < ray->len_y - ray->delta_dist_y / 2)
		return (false);
	else if (door->state == DOOR_CLOSED
		|| (door->state != DOOR_CLOSED && tex_pos < door->open))
	{
		ray->len_y += ray->delta_dist_y / 2;
		ray->side = RAY_HIT_Y;
		if (tex_pos < door->open)
			*offset = door->open;
		return (true);
	}
	return (false);
}

static bool	_ray_intersect(t_game *g, t_ray *ray, int8_t *offset)
{
	const char	tile = g->c->map[ray->map_y][ray->map_x];

	if (tile == '1')
		return (true);
	else if (tile == '|')
	{
		return (_vertical_door_intersect(g, ray, offset));
	}
	else if (tile == '-')
	{
		return (_horizontal_door_intersect(g, ray, offset));
	}
	else
		return (false);
}

void	c_ray_raycasting_loop_bonus(t_game *g, t_ray *ray, int8_t *offset)
{
	while (1)
	{
		if (ray->map_x < 0 || (t_uint)ray->map_x >= g->c->sx
			|| ray->map_y < 0 || (t_uint)ray->map_y >= g->c->sy
			|| _ray_intersect(g, ray, offset))
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
