/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:47:30 by pbremond          #+#    #+#             */
/*   Updated: 2022/04/28 22:44:58 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <libft.h>

void	c_toggle_mouselook(t_game *g)
{
	if (!g->m_cap)
	{
		mlx_mouse_hide();
		mlx_mouse_move(g->mw, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	}
	else
		mlx_mouse_show();
	g->m_cap ^= 1;
}

void	c_mouse_look(t_game *g)
{
	const t_ipair	old_m = {WIN_WIDTH / 2, WIN_HEIGHT / 2};
	t_ipair			mouse;
	int				delta;

	mlx_mouse_get_pos(g->mw, &mouse.a, &mouse.b);
	delta = mouse.a - old_m.a;
	c_math_rotate_vector(&g->dx, &g->dy, (float)(delta * 0.003f));
	c_math_rotate_vector(&g->cx, &g->cy, (float)(delta * 0.003f));
	mlx_mouse_move(g->mw, old_m.a, old_m.b);
}
