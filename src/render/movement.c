/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 10:48:39 by pbremond          #+#    #+#             */
/*   Updated: 2024/12/18 17:09:14 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <libft.h>

void	c_player_decel(t_game *g)
{
	const double	pos_decel = DECEL * g->dt_sec;
	const double	cam_decel = ANG_VEL_DEC * g->dt_sec;

	if (!(g->k & (KEYS_W | KEYS_S)))
	{
		if (g->vy > 0.0f)
			g->vy -= fminf(pos_decel, g->vy);
		else if (g->vy < 0.0f)
			g->vy -= fmaxf(-pos_decel, g->vy);
	}
	if (!(g->k & (KEYS_A | KEYS_D)))
	{
		if (g->vx > 0.0f)
			g->vx -= fminf(pos_decel, g->vx);
		else if (g->vx < 0.0f)
			g->vx -= fmaxf(-pos_decel, g->vx);
	}
	if (!(g->k & (KEYS_LEFT | KEYS_RIGHT)))
	{
		if (g->va > 0.0f)
			g->va -= fminf(cam_decel, g->va);
		else if (g->va < 0.0f)
			g->va -= fmaxf(-cam_decel, g->va);
	}
}

static void	_player_rotation(t_game *g)
{
	if (g->k & KEYS_LEFT && g->va > -ANG_VEL_MAX)
		g->va -= ANG_VEL_ACC * g->dt_sec;
	else if (g->k & KEYS_RIGHT && g->va < ANG_VEL_MAX)
		g->va += ANG_VEL_ACC * g->dt_sec;
	if (g->va != 0.0f)
	{
		c_math_rotate_vector(&g->dx, &g->dy, g->va * g->dt_sec * 1000);
		c_math_rotate_vector(&g->cx, &g->cy, g->va * g->dt_sec * 1000);
	}
}

void	c_move_player(t_game *g)
{
	if (g->k & KEYS_W && g->vy < MAX_VEL)
		g->vy += ACCEL * g->dt_sec;
	if (g->k & KEYS_S && g->vy > -MAX_VEL)
		g->vy -= ACCEL * g->dt_sec;
	if (g->k & KEYS_D && g->vx < MAX_VEL)
		g->vx += ACCEL * g->dt_sec;
	if (g->k & KEYS_A && g->vx > -MAX_VEL)
		g->vx -= ACCEL * g->dt_sec;
	_player_rotation(g);
	c_collision_handling(g,
		(g->vy * g->dx) + (g->vx * -g->dy),
		(g->vy * g->dy) + (g->vx * g->dx));
}
