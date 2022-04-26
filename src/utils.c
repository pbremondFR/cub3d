/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 23:28:42 by pbremond          #+#    #+#             */
/*   Updated: 2022/04/26 23:46:11 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

int	c_exit_program(void *g_handle)
{
	t_game	*g;

	g = (t_game *)g_handle;
	ft_split_free(g->c->map, g->c->sy);
	mlx_destroy_image(g->mlx, g->c->n->i);
	free(g->c->n);
	mlx_destroy_image(g->mlx, g->c->s->i);
	free(g->c->s);
	mlx_destroy_image(g->mlx, g->c->e->i);
	free(g->c->e);
	mlx_destroy_image(g->mlx, g->c->w->i);
	free(g->c->w);
	mlx_destroy_image(g->mlx, g->f.i);
	mlx_destroy_window(g->mlx, g->mw);
	// while (1)
	// 	;
	exit(0);
	return (0);
}
