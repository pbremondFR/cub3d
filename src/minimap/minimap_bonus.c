/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 20:39:41 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/05 20:07:56 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d_bonus.h>

// Easy to write ? Yes ! Optimized ? No ! Should I come back to this and want
// to make it perform better, I'd need to use cache locality.
void	_draw_minimap_line(t_game *g, t_ipair coords, int map_y)
{
	int		i;
	t_ipair	tgt_map;

	tgt_map.b = map_y;
	i = 0;
	while (i < MINIMAP_WIDTH)
	{
		tgt_map.a = (int)g->x - (MINIMAP_WIDTH / 2) + i;
		if (tgt_map.a < 0 || tgt_map.b < 0
			|| (t_uint)tgt_map.a >= g->c->sx || (t_uint)tgt_map.b >= g->c->sy
			|| g->c->map[tgt_map.b][tgt_map.a] == ' ')
			c_draw_square_2(&g->olay, coords, 0xff000000ff000000, MM_TIL_SIZ);
		else if (tgt_map.a == (int)g->x && tgt_map.b == (int)g->y)
			c_draw_square_2(&g->olay, coords, 0xff0000, MM_TIL_SIZ);
		else if (g->c->map[tgt_map.b][tgt_map.a] == '0')
			c_draw_square_2(&g->olay, coords, g->c->f, MM_TIL_SIZ);
		else if (g->c->map[tgt_map.b][tgt_map.a] == '1')
			c_draw_square_2(&g->olay, coords, 0xffffff - g->c->f, MM_TIL_SIZ);
		else
			c_draw_square_2(&g->olay, coords, 0xff00ff, MM_TIL_SIZ);
		coords.a += MM_TIL_SIZ;
		++i;
	}
}

void	c_minimap_render(t_game *g, int x, int y)
{
	int		i;
	t_ipair	coords;
	int		map_y;
	t_pnt	dir_1;
	t_pnt	dir_2;

	coords.a = x;
	coords.b = y;
	i = 0;
	while (i < MINIMAP_HEIGHT)
	{
		map_y = (int)g->y - (MINIMAP_HEIGHT / 2) + i;
		_draw_minimap_line(g, coords, map_y);
		coords.b += MM_TIL_SIZ;
		++i;
	}
	dir_1.x = (float)g->olay.w / 2;
	dir_1.y = (float)g->olay.h / 2;
	dir_2.x = dir_1.x + (g->dx * (MM_TIL_SIZ / 2));
	dir_2.y = dir_1.y + (g->dy * (MM_TIL_SIZ / 2));
	c_draw_line(&g->olay, dir_1, dir_2, 0x00ffff);
}
