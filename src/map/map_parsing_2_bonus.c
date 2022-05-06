/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 22:46:21 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/06 23:01:31 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d_bonus.h>

void	c_init_sprites_pos(t_game *g)
{
	int		y;
	int		x;
	t_sprt	*new_sprt;

	y = -1;
	while ((t_uint)++y < g->c->sy)
	{
		x = -1;
		while ((t_uint)++x < g->c->sx)
		{
			if (ft_strchr("2345", g->c->map[y][x]))
			{
				new_sprt = c_create_sprite(g, g->c->map[y][x],
						(float)x + 0.5f, (float)y + 0.5f);
				if (new_sprt == NULL)
					c_exit_program(g);
				ft_lstadd_back(&g->sprts_lst, ft_lstnew(new_sprt));
				g->n_sprt++;
			}
		}
	}
}
