/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 21:29:28 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/28 09:13:10 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

static int	_get_pos_in_texture(t_ipair line_coords, int i, int tex_width)
{
	float	pos;

	pos = (float)(i - line_coords.a) / (line_coords.b - line_coords.a);
	pos = pos * tex_width;
	return (c_min((int)pos, tex_width - 1));
}

/*
 *        ┬ line_coords.a
 *        │
 *    i►┌─┼────SCREEN──────┐
 *      │ │                │
 *      │ │                │
 *      │ │                │
 *      │ │                │
 *      │ │                │
 *  end►└─┼────────────────┘
 *        │
 *        ┴ line_coords.b
 */

void	draw_textures_wall_line(t_game *g, t_tex_line *texture, int frame_x,
	int height)
{
	const int	*tex_addr = (const int *)texture->addr;
	t_ipair		line_coords;
	int			i;
	int			end;
	int			pos_in_texture;

	line_coords.a = (-height / 2) + (WIN_HEIGHT / 2);
	line_coords.b = (height / 2) + (WIN_HEIGHT / 2);
	if (line_coords.a < 0)
		i = 0;
	else
		i = line_coords.a;
	if (line_coords.b > WIN_HEIGHT - 1)
		end = WIN_HEIGHT - 1;
	else
		end = line_coords.b;
	while (i < end)
	{
		pos_in_texture = _get_pos_in_texture(line_coords, i, texture->w);
		my_mlx_pixel_put(&g->f, frame_x, i, tex_addr[pos_in_texture]);
		++i;
	}
}
