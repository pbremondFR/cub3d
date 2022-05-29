/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_barrel_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 09:16:06 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/29 01:20:48 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

static void	_barrel_explode(t_game *g, t_sprt *sprt)
{
	if (sprt->state == 1)
		sprt->cur_tile = 4;
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
	if (g->t.tv_sec * 1000 + (g->t.tv_nsec / 1e6) < sprt->next_time)
		return ;
	if (sprt->state == 0
		&& fabsf(c_math_get_sq_dist(sprt->x, g->x, sprt->y, g->y)) < 1.0f)
		sprt->state = 1;
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
