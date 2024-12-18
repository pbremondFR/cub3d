/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:47:30 by pbremond          #+#    #+#             */
/*   Updated: 2024/12/18 17:10:25 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <libft.h>

#ifdef __linux__

// What a brilliant fucking idea, let's just change function signatures across
// platforms!

void	c_toggle_mouselook(t_game *g)
{
	if (!g->m_cap)
	{
		mlx_mouse_hide(g->mlx, g->mw);
		mlx_mouse_move(g->mlx, g->mw, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	}
	else
		mlx_mouse_show(g->mlx, g->mw);
	g->m_cap ^= 1;
}

// XXX: Since the switch to Linux, mouselook is trash :(
void	c_mouse_look(t_game *g)
{
	const t_ipair	win_center = {WIN_WIDTH / 2, WIN_HEIGHT / 2};
	t_ipair			mouse;
	int				delta;

	mlx_mouse_get_pos(g->mlx, g->mw, &mouse.a, &mouse.b);
	delta = mouse.a - win_center.a;
	c_math_rotate_vector(&g->dx, &g->dy,
		(float)(delta * MOUSE_SENS * g->dt_sec * 400));
	c_math_rotate_vector(&g->cx, &g->cy,
		(float)(delta * MOUSE_SENS * g->dt_sec * 400));
	mlx_mouse_move(g->mlx, g->mw, win_center.a, win_center.b);
}

#else

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
	const t_ipair	win_center = {WIN_WIDTH / 2, WIN_HEIGHT / 2};
	t_ipair			mouse;
	int				delta;

	mlx_mouse_get_pos(g->mw, &mouse.a, &mouse.b);
	delta = mouse.a - win_center.a;
	c_math_rotate_vector(&g->dx, &g->dy, (float)(delta * MOUSE_SENS));
	c_math_rotate_vector(&g->cx, &g->cy, (float)(delta * MOUSE_SENS));
	mlx_mouse_move(g->mw, win_center.a, win_center.b);
}

#endif
