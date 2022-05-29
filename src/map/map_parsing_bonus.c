/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 22:46:21 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/29 05:53:11 by pbremond         ###   ########.fr       */
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
			if (ft_strchr(SPRITE_IDS, g->c->map[y][x]))
			{
				new_sprt = c_create_sprite(g, g->c->map[y][x],
						(float)x + 0.5f, (float)y + 0.5f);
				if (new_sprt == NULL)
					c_exit_program(g, 0);
				ft_lstadd_back(&g->sprts_lst, ft_lstnew(new_sprt));
				g->n_sprt++;
				g->c->map[y][x] = '0';
			}
		}
	}
}

static t_uint	_count_number_of_doors(char **map, t_uint sx,
	t_uint sy)
{
	int		x;
	int		y;
	t_uint	count;

	count = 0;
	y = -1;
	while ((t_uint)++y < sy)
	{
		x = -1;
		while ((t_uint)++x < sx)
		{
			if (ft_strchr("|-", map[y][x]))
				++count;
		}
	}
	return (count);
}

// Sorry const... It's for your own good, I promise.
static void	_init_t_door(t_door *door, int x, int y)
{
	door->offset = 100;
	door->state = DOOR_CLOSED;
	*(int *)(&door->x) = x;
	*(int *)(&door->y) = y;
	door->next_time = 0L;
}

void	c_init_doors(t_cub *c)
{
	const t_uint	n_doors = _count_number_of_doors(c->map, c->sx, c->sy);
	int				x;
	int				y;
	int				i;

	c->doors = (t_door *)malloc(sizeof(t_door) * n_doors);
	if (c->doors == NULL)
		c_fatal_exit();
	c->n_doors = n_doors;
	i = 0;
	y = -1;
	while ((t_uint)++y < c->sy)
	{
		x = -1;
		while ((t_uint)++x < c->sx)
		{
			if (ft_strchr("|-", c->map[y][x]))
				_init_t_door(&c->doors[i++], x, y);
		}
	}
}
