/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 21:29:28 by pbremond          #+#    #+#             */
/*   Updated: 2022/04/27 21:34:25 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

static int	_get_pos_in_texture(t_ipair line_coords, int i, int ls, int print)
{
	float	pos;

	if (print)
		printf("i: %d\nline: %d\t%d\n", i, line_coords.a, line_coords.b);
	pos = ((float)(i - line_coords.a) / (float)(line_coords.b - line_coords.a));
	if (print)
		printf("posf: %.5f\n", pos);
	pos = pos * ls;
	if (print)
		printf("posd: %d\n", (int)pos);
	return ((int)pos);
}

void	draw_textures_wall_line(t_game *g, t_tex_line *texture, int frame_x,
	int height)
{
	const int	*tex_addr = (const int *)texture->addr;
	// const int	oct_line_size = texture->ls / 4;
	t_ipair		line_coords;
	int			i;
	int			end;
	int			pos_in_texture;

	line_coords.a = (-height / 2) + (WIN_HEIGHT / 2); // Start
	line_coords.b = (height / 2) + (WIN_HEIGHT / 2); // End
	if (line_coords.a < 0)
		i = 0;
	else
		i = line_coords.a;
	if (line_coords.b > WIN_HEIGHT - 1)
		end = WIN_HEIGHT - 1;
	else
		end = line_coords.b;
	while (i < end) // i - line_coords.a -> position within texture
	{
		pos_in_texture = _get_pos_in_texture(line_coords, i, texture->w, 0);
		my_mlx_pixel_put(&g->f, frame_x, i, tex_addr[pos_in_texture]);
		++i;
	}
}
