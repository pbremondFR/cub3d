/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 20:39:41 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/29 08:23:24 by pbremond         ###   ########.fr       */
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

static void	_draw_player_icon(t_game *g, t_img *img)
{
	const int	icon_rad = 5;
	t_pnt		dir_1;
	t_pnt		dir_2;
	t_ipair		coords;

	coords.a = img->w / 2 - icon_rad / 2;
	coords.b = img->h / 2 - icon_rad / 2;
	c_draw_square_2(img, coords, 0x0, icon_rad);
	dir_1.x = (float)img->w / 2;
	dir_1.y = (float)img->h / 2;
	dir_2.x = dir_1.x + (g->dx * (MM_TIL_SIZ / 2));
	dir_2.y = dir_1.y + (g->dy * (MM_TIL_SIZ / 2));
	c_draw_line(img, dir_1, dir_2, 0xffffff);
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
