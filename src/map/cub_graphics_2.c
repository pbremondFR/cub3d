/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_graphics_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 15:26:52 by pbremond          #+#    #+#             */
/*   Updated: 2022/04/26 23:07:13 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

// FIXME: SEGFAULT ??? AGAIN ???!!!
static void	_reorder_buffers(t_uint *img_buf, t_uint *buffer, int height,
	int line_size)
{
	int		i;
	int		j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < line_size)
		{
			buffer[i * line_size + j] = img_buf[i + line_size * j];
			++j;
		}
		++i;
	}
}

// TESTME: I'm like 90% sure this will spectacularily fuck up for non-square
// textures :)
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
	ft_memcpy(img->addr, buffer, buf_siz);
	free(buffer);
	return (EXIT_SUCCESS);
}
