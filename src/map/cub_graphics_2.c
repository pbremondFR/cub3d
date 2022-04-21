/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_graphics_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 15:26:52 by pbremond          #+#    #+#             */
/*   Updated: 2022/04/21 18:16:03 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

static void	_swap_buffers(t_uint *img_buf, t_uint *buffer, int buf_siz,
	int line_size)
{
	int		i;
	int		j;

	i = 0;
	while (i < buf_siz / line_size)
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

int	c_opt_texture_for_cache(t_img *img)
{
	t_uint		*buffer;

	buffer = (t_uint *)malloc(img->w * img->ls);
	if (buffer == NULL)
		return (EXIT_FAILURE);
	ft_memcpy(buffer, img->addr, img->h * img->ls);
	_swap_buffers((t_uint *)img->addr, buffer, img->h * img->ls, img->ls / 4);
	ft_memcpy(img->addr, buffer, img->h * img->ls);
	ft_printf("ls: %d (%d)\n", img->ls, img->ls / 4);
	ft_printf("h: %d\tw: %d\n", img->h, img->w);
	free(buffer);
	return (EXIT_SUCCESS);
}
