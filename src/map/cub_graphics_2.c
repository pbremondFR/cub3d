/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_graphics_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 15:26:52 by pbremond          #+#    #+#             */
/*   Updated: 2022/04/27 21:40:50 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

// TESTME: Most probably fixed that segfault.
// NOTE: Does NOT work with textures that aren't squares.
static void	_reorder_buffers(t_uint *img_buf, t_uint *buffer, int side_len,
	int line_size)
{
	int		i;
	int		j;

	i = -1;
	while (++i < side_len)
	{
		j = -1;
		while (++j < side_len)
		{
			buffer[(i * line_size) + j] = img_buf[i + (line_size * j)];
		}
	}
}

// Bitmasks all contents of destination buffer to keep eveything but the
// transparency bits. 
void	_remove_transparency(t_uint *dest, int height, int ls)
{
	int	i;

	i = 0;
	while (i < height * ls)
		dest[i++] &= 0xffffff;
}

// TODO: Safety against non-square textures
// Optimizes a texture in memory, such that it benefits as much as possible from
// the CPU cache when drawing a wall. It's thus stored column by column, instead
// of line by line. Origin is still top-left.
int	c_opt_texture_for_cache(t_img *img)
{
	t_uint		*buffer;
	int			buf_siz;

	buf_siz = img->h * img->ls;
	buffer = (t_uint *)malloc(buf_siz);
	if (buffer == NULL)
		return (EXIT_FAILURE);
	ft_memcpy(buffer, img->addr, buf_siz);
	ft_printf("ls: %d (%d)\n", img->ls, img->ls / 4);
	ft_printf("buf_siz: %d\n", buf_siz);
	ft_printf("h: %d\tw: %d\n", img->h, img->w);
	_reorder_buffers((t_uint *)img->addr, buffer, img->h, img->ls / 4);
	_remove_transparency(buffer, img->h, img->ls / 4);
	ft_memcpy(img->addr, buffer, buf_siz);
	free(buffer);
	return (EXIT_SUCCESS);
}
