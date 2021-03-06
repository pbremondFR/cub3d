/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 10:48:39 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/29 03:52:35 by pbremond         ###   ########.fr       */
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

static void	_player_rotation(t_game *g)
{
	if (g->k & KEYS_LEFT && g->va > -ANG_VEL_MAX)
		g->va -= ANG_VEL_ACC;
	else if (g->k & KEYS_RIGHT && g->va < ANG_VEL_MAX)
		g->va += ANG_VEL_ACC;
	if (g->va != 0.0f)
	{
		c_math_rotate_vector(&g->dx, &g->dy, g->va);
		c_math_rotate_vector(&g->cx, &g->cy, g->va);
	}
}

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
	_player_rotation(g);
	c_collision_handling(g,
		(g->vy * g->dx) + (g->vx * -g->dy),
		(g->vy * g->dy) + (g->vx * g->dx));
}
