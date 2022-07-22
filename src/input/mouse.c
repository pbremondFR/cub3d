/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:47:30 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/19 14:40:14 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <libft.h>

// Why the fuck does MLX segfault when trying to use mouse functions ???
void	c_toggle_mouselook(t_game *g)
{
	// if (!g->m_cap)
	// {
	// 	mlx_mouse_hide();
	// 	mlx_mouse_move(g->mw, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	// }
	// else
	// 	mlx_mouse_show();
	// g->m_cap ^= 1;
	(void)g;
}

void	c_mouse_look(t_game *g)
{
	const t_ipair	old_m = {WIN_WIDTH / 2, WIN_HEIGHT / 2};
	t_ipair			mouse;
	int				delta;

	mlx_mouse_get_pos(g->mw, &mouse.a, &mouse.b);
	delta = mouse.a - old_m.a;
	c_math_rotate_vector(&g->dx, &g->dy, (float)(delta * MOUSE_SENS));
	c_math_rotate_vector(&g->cx, &g->cy, (float)(delta * MOUSE_SENS));
	mlx_mouse_move(g->mw, old_m.a, old_m.b);
}

int	c_mousepress_handler(int key, int x, int y, void *handle)
{
	t_game	*g;

	(void)x;
	(void)y;
	g = (t_game *)handle;
	if (key == KEYC_M1)
		g->k |= KEYS_M1;
	else if (key == KEYC_M2)
		g->k |= KEYS_M2;
	else if (key == KEYC_M3)
		g->k |= KEYS_M3;
	return (0);
}

int	c_mouserelease_handler(int key, int x, int y, void *handle)
{
	t_game	*g;

	(void)x;
	(void)y;
	g = (t_game *)handle;
	if (key == KEYC_M1)
		g->k ^= KEYS_M1;
	else if (key == KEYC_M2)
		g->k ^= KEYS_M2;
	else if (key == KEYC_M3)
		g->k ^= KEYS_M3;
	return (0);
}
