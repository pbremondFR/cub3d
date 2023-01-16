/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_barrel_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 09:16:06 by pbremond          #+#    #+#             */
/*   Updated: 2023/01/16 17:31:58 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

static void	_explosion_move_player(t_game *g, const t_sprt *sprt)
{
	t_pnt	expl_vec;
	float	inv_mag;

	expl_vec.x = g->x - (sprt->x);
	expl_vec.y = g->y - (sprt->y);
	inv_mag = 1 / sqrtf((expl_vec.x * expl_vec.x) + (expl_vec.y * expl_vec.y));
	expl_vec.x *= inv_mag / 10;
	expl_vec.y *= inv_mag / 10;
	g->vy = (expl_vec.y * g->dy) + (expl_vec.x * g->dx);
	g->vx = (g->dy * -expl_vec.x) + (g->dx * expl_vec.y);
}

static void	_barrel_explode(t_game *g, t_sprt *sprt)
{
	if (sprt->state == 1)
	{
		sprt->cur_tile = 4;
		_explosion_move_player(g, sprt);
	}
	sprt->state = 2;
	if (sprt->cur_tile >= sprt->n_tiles)
	{
		sprt->del = true;
	}
	else
	{
		sprt->addr = c_get_const_target_addr(sprt->i, 0,
				sprt->cur_tile * sprt->t_h);
		sprt->next_time = g->t.tv_sec * 1000 + (g->t.tv_nsec / 1e6 + 110);
	}
}

void	c_barrel_animate_routine(t_game *g, t_sprt *sprt)
{
	if (sprt->state == 0
		&& fabsf(c_math_get_sq_dist(sprt->x, g->x, sprt->y, g->y)) < 1.0f)
		sprt->state = 1;
	else if (g->t.tv_sec * 1000 + (g->t.tv_nsec / 1e6) < sprt->next_time)
		return ;
	sprt->cur_tile += 1;
	if (sprt->state == 0)
	{
		if (sprt->cur_tile >= 3)
			sprt->cur_tile = 0;
		sprt->addr = c_get_const_target_addr(sprt->i, 0,
				sprt->cur_tile * sprt->t_h);
		sprt->next_time = g->t.tv_sec * 1000 + (g->t.tv_nsec / 1e6 + 500);
	}
	else
		_barrel_explode(g, sprt);
}
