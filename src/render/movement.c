/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 10:48:39 by pbremond          #+#    #+#             */
/*   Updated: 2022/04/21 11:59:40 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <libft.h>

void	c_player_decel(float *vx, float *vy, float *va, int keystate)
{
	if (!(keystate & (KEYS_W | KEYS_S)))
	{
		if (*vy > 0.0f)
			*vy -= fminf(DECEL, *vy);
		else if (*vy < 0.0f)
			*vy -= fmaxf(-DECEL, *vy);
	}
	if (!(keystate & (KEYS_A | KEYS_D)))
	{
		if (*vx > 0.0f)
			*vx -= fminf(DECEL, *vx);
		else if (*vx < 0.0f)
			*vx -= fmaxf(-DECEL, *vx);
	}
	if (!(keystate & (KEYS_LEFT | KEYS_RIGHT)))
	{
		if (*va > 0.0f)
			*va -= fminf(ANG_VEL_DEC, *va);
		else if (*va < 0.0f)
			*va -= fmaxf(-ANG_VEL_DEC, *va);
	}
}

// TODO: Optimize me
static void	_player_rotation(t_game *g)
{
	if (g->k & KEYS_LEFT && g->va > -ANG_VEL_MAX)
		g->va -= ANG_VEL_ACC;
	if (g->k & KEYS_RIGHT && g->va < ANG_VEL_MAX)
		g->va += ANG_VEL_ACC;
	if (g->va != 0.0f)
	{
		c_math_rotate_vector(&g->dx, &g->dy, g->va);
		c_math_rotate_vector(&g->cx, &g->cy, g->va);
	}
}

// 1: Cast a ray from player pos to next known position
// 2: If ray is shorter than next position then adjust player pos to be against
// the wall, and kill x or y velocity
// Else just add velocity to pos like normal

// TODO: Fix the velocity bump problem
void	c_collision_handling(t_game *g, float next_x, float next_y)
{
	t_ray	ray;
	// float	len_x;
	// float	len_y;
	float	dist_to_next;
	float	dist_to_next_abs;

	ray.map_x = (int)g->x;
	ray.map_y = (int)g->y;
	dist_to_next = c_math_get_dist(g->x, next_x, g->y, next_y);
	dist_to_next_abs = fabsf(dist_to_next);
	ray.dir_x = (next_x - g->x) / dist_to_next_abs;
	ray.dir_y = (next_y - g->y) / dist_to_next_abs;
	ray.delta_dist_x = fabsf(1 / ray.dir_x);
	ray.delta_dist_y = fabsf(1 / ray.dir_y);
	c_ray_calc_step_and_len(&ray, g->x, g->y);
	c_ray_raycasting_loop(g, &ray);
	if (ray.side == RAY_HIT_X)
		ray.c_plane_len = (ray.len_x - ray.delta_dist_x);
	else
		ray.c_plane_len = (ray.len_y - ray.delta_dist_y);
	if (ray.c_plane_len - 0.1f < dist_to_next_abs)
	{
		if (ray.side == RAY_HIT_X)
		{
			// g->x += (ray.c_plane_len + 0.1f) * ray.dir_x;
			// g->y = (float)ray.map_y;
			g->y = next_y;
			printf("%sXXXXXXXXXXXXX%s\n", RED, RESET);
		}
		else
		{
			// g->x = (float)ray.map_x;
			// g->y += (ray.c_plane_len + 0.1f) * ray.dir_y;
			g->x = next_x;
			printf("%sYYYYYYYYYYYYY%s\n", RED, RESET);
		}
		// g->x += ((ray.c_plane_len - 0.1f) * ray.dir_x);
		// g->y += ((ray.c_plane_len - 0.1f) * ray.dir_y);
	}
	else
	{
		g->x = next_x;
		g->y = next_y;
	}
	// printf("Collision dir: %.3f \t%.3f\n", ray.dir_x, ray.dir_y);
	// printf("Ray plane len: %.2f\n", ray.c_plane_len);
}

// TODO: Make a proper exit function
void	c_move_player(t_game *g)
{
	if (g->k & KEYS_W && g->vy < MAX_VEL)
		g->vy += ACCEL;
	if (g->k & KEYS_S && g->vy > -MAX_VEL)
		g->vy -= ACCEL;
	if (g->k & KEYS_D && g->vx < MAX_VEL)
		g->vx += ACCEL;
	if (g->k & KEYS_A && g->vx > -MAX_VEL)
		g->vx -= ACCEL;
	if (g->k == (KEYS_ESC | KEYS_SPA))
		exit(0);
	// if (g->k & (KEYS_LEFT | KEYS_RIGHT))
	_player_rotation(g);
	c_collision_handling(g,
		g->x + (g->vy * g->dx) + (g->vx * -g->dy),
		g->y + (g->vy * g->dy) + (g->vx * g->dx));
	// g->x += (g->vy * g->dx) + (g->vx * -g->dy);
	// g->y += (g->vy * g->dy) + (g->vx * g->dx);
}
