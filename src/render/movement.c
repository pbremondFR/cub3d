/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 10:48:39 by pbremond          #+#    #+#             */
/*   Updated: 2022/04/07 15:20:41 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <libft.h>

void	c_player_decel(float *vx, float *vy, int keystate)
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
}
// TODO: Optimize me !!!
static void	_player_rotation(t_game *g)
{
	if (g->k & KEYS_LEFT)
	{
		c_math_rotate_vector(&g->dx, &g->dy, -ANG_VEL);
		c_math_rotate_vector(&g->px, &g->py, -ANG_VEL);
	}
	if (g->k & KEYS_RIGHT)
	{
		c_math_rotate_vector(&g->dx, &g->dy, ANG_VEL);
		c_math_rotate_vector(&g->px, &g->py, ANG_VEL);
	}
}

// static void	_collision_check(t_game *g)
// {
// 	char	**map;

// 	map = g->c->map;
// }

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
	if (g->k & (KEYS_LEFT | KEYS_RIGHT))
		_player_rotation(g);
	g->x += (g->vy * g->dx) + (g->vx * -g->dy);
	g->y += (g->vy * g->dy) + (g->vx * g->dx);
	// if (g->x * MAP_TILE_SIZE + PLY_HITBX_RAD > WIN_FWIDTH)
	// 	g->x = (WIN_FWIDTH - PLY_HITBX_RAD) / MAP_TILE_SIZE;
	// else if (g->x * MAP_TILE_SIZE - PLY_HITBX_RAD < 0.0f)
	// 	g->x = (0.0f + PLY_HITBX_RAD) / MAP_TILE_SIZE;
	// if (g->y * MAP_TILE_SIZE + PLY_HITBX_RAD > WIN_FHEIGHT)
	// 	g->y = (WIN_FHEIGHT - PLY_HITBX_RAD) / MAP_TILE_SIZE;
	// else if (g->y * MAP_TILE_SIZE - PLY_HITBX_RAD < 0.0f)
	// 	g->y = (0.0f + PLY_HITBX_RAD) / MAP_TILE_SIZE;
}
