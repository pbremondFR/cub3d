/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 23:28:42 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/16 19:44:39 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

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

// TODO: Handle exit code
// TODO: Free up everything just to be sure, evem though pointers are
// still reachable
// TESTME: Just make sure nothing ever leaks
int	c_exit_program(void *g_handle)
{
	t_game	*g;

	g = (t_game *)g_handle;
	if (g->c->map)
		ft_split_free(g->c->map, g->c->sy);
	c_delete_t_img_ptr(&g->c->n, g);
	c_delete_t_img_ptr(&g->c->s, g);
	c_delete_t_img_ptr(&g->c->e, g);
	c_delete_t_img_ptr(&g->c->w, g);
	if (g->f.i)
		mlx_destroy_image(g->mlx, g->f.i);
	mlx_destroy_window(g->mlx, g->mw);
	while (1)
		;
	exit(0);
	return (0);
}
