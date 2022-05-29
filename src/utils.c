/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 23:28:42 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/29 05:46:24 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

// #define LEAK_CHECK

void	c_delete_t_img_ptr(t_img **img_ptr, t_game *g)
{
	t_img	*img;

	img = *img_ptr;
	if (img)
	{
		mlx_destroy_image(g->mlx, img->i);
		free(img);
	}
	img_ptr = NULL;
}

int	c_exit_program_hook(void *g_handle)
{
	c_exit_program((t_game *)g_handle, 0);
	return (0);
}

#ifdef LEAK_CHECK

int	c_exit_program(t_game *g, int code)
{
	if (g->c->map)
		ft_split_free(g->c->map, g->c->sy);
	mlx_destroy_window(g->mlx, g->mw);
	while (1)
		;
	exit(code);
	return (code);
}

#else

int	c_exit_program(t_game *g, int code)
{
	if (g->c->map)
		ft_split_free(g->c->map, g->c->sy);
	mlx_destroy_window(g->mlx, g->mw);
	exit(code);
	return (code);
}

#endif

// To be used when all hell breaks loose, i.e. malloc failure.
void	c_fatal_exit(void)
{
	write(2, "Fatal error: ", 13);
	perror(strerror(errno));
	exit(errno);
}
