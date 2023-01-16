/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 20:39:41 by pbremond          #+#    #+#             */
/*   Updated: 2023/01/16 19:41:57 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d_bonus.h>

// Brilliantly unreadable.
static t_uint	_get_colour(const t_game *g, char tile)
{
	const t_uint	f_inv = (0xffffff - g->c->f);

	if (tile == '0')
		return (g->c->f);
	else if (tile == '1')
		return (f_inv);
	else if (tile == '-' || tile == '|')
		return ((((f_inv >> 16 & 0xff) / 2) << 16
				| ((f_inv >> 8 & 0xff) / 2) << 8
				| (f_inv & 0xff) / 2));
	else
		return (0xff00ff);
}

static void	_draw_minimap_line(t_game *g, t_ipair offset, float pos_y,
	int map_y)
{
	const float	step = (1.0f / MINIMAP_TILE_SIZ);
	float		i;
	t_ipair		tgt_map;
	t_uint		colour;

	tgt_map.b = map_y;
	i = 0.0f;
	while (i < MINIMAP_WIDTH)
	{
		tgt_map.a = floorf(g->x - (MINIMAP_WIDTH / 2.0f) + i);
		if (tgt_map.a < 0 || tgt_map.b < 0
			|| (t_uint)tgt_map.a >= g->c->sx || (t_uint)tgt_map.b >= g->c->sy
			|| g->c->map[tgt_map.b][tgt_map.a] == ' ')
			my_mlx_pixel_put(&g->olay, (int)((i) * MM_TIL_SIZ + offset.a),
				((pos_y) * MM_TIL_SIZ + offset.b), 0xc0000000);
		else
		{
			colour = _get_colour(g, g->c->map[tgt_map.b][tgt_map.a]);
			my_mlx_pixel_put(&g->olay, (int)(i * MM_TIL_SIZ + offset.a),
				(pos_y * MM_TIL_SIZ + offset.b), colour);
		}
		i += step;
	}
}

void	c_draw_triangle(t_img *img, t_pnt a, t_pnt b, t_pnt c);

static void	_draw_player_icon(t_game *g, t_img *img)
{
	const t_pnt	center = {img->w / 2.0f, img->h / 2.0f};
	t_pnt		pnt[4];

	pnt[0].x = center.x + (g->dx * (MM_TIL_SIZ / 2));
	pnt[0].y = center.y + (g->dy * (MM_TIL_SIZ / 2));
	pnt[1].x = center.x + (-g->dx * (MM_TIL_SIZ / 2)
			+ g->dy * (MM_TIL_SIZ / 2));
	pnt[1].y = center.y + (-g->dy * (MM_TIL_SIZ / 2)
			+ -g->dx * (MM_TIL_SIZ / 2));
	pnt[2].x = center.x + (-g->dx * (MM_TIL_SIZ / 2)) / 2;
	pnt[2].y = center.y + (-g->dy * (MM_TIL_SIZ / 2)) / 2;
	pnt[3].x = center.x + (-g->dx * (MM_TIL_SIZ / 2)
			+ -g->dy * (MM_TIL_SIZ / 2));
	pnt[3].y = center.y + (-g->dy * (MM_TIL_SIZ / 2)
			+ g->dx * (MM_TIL_SIZ / 2));
	// c_draw_triangle(img, pnt[0], pnt[1], pnt[2]);
	// c_draw_triangle(img, pnt[2], pnt[3], pnt[0]);
	c_draw_line(img, pnt[0], pnt[1], 0xffffff);
	c_draw_line(img, pnt[1], pnt[2], 0xffffff);
	c_draw_line(img, pnt[2], pnt[3], 0xffffff);
	c_draw_line(img, pnt[3], pnt[0], 0xffffff);
}

void	c_minimap_render(t_game *g, int x, int y)
{
	const float	step = (1.0f / MINIMAP_TILE_SIZ);
	float		i;
	t_ipair		coords;
	int			map_y;

	coords.a = x;
	coords.b = y;
	i = 0.0f;
	while (i < MINIMAP_HEIGHT)
	{
		map_y = floorf(g->y - ((float)MINIMAP_HEIGHT / 2.0f) + i);
		_draw_minimap_line(g, coords, i, map_y);
		i += step;
	}
	_draw_player_icon(g, &g->olay);
}
