/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 20:46:15 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/19 15:44:16 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d_bonus.h>

// Changes how much door is opened/closed by DOOR_OPEN_DELTA.
// door->state has to be +1 or -1, corresponding to an opening or a closing.
void	c_move_door(t_door *door)
{
	door->open += DOOR_OPEN_DELTA * -door->state;
	if (door->open <= 0)
	{
		door->state = DOOR_OPENED;
		door->open = 0;
	}
	else if (door->open >= 100)
	{
		door->state = DOOR_CLOSED;
		door->open = 100;
	}
}

// Goes through door array to find door with matching x and y positions
t_door	*c_get_door(t_door *doors, t_uint n_doors, int x, int y)
{
	t_uint	i;

	i = 0;
	while (i < n_doors)
	{
		if (doors[i].x == x && doors[i].y == y)
			return (&doors[i]);
		++i;
	}
	return (NULL);
}

// Animates doors. That's it.
void	c_doors_routine(const struct timespec *t, t_door *doors, t_uint n_doors)
{
	t_uint	i;

	i = 0;
	while (i < n_doors)
	{
		if (doors[i].state == DOOR_CLOSED || doors[i].state == DOOR_OPENED)
		{
			++i;
			continue ;
		}
		else if (c_is_time_over(t, doors[i].next_time))
		{
			c_move_door(&doors[i]);
			doors[i].next_time += DOOR_PERIOD_MS;
		}
		++i;
	}
}

// Returns coordinates of point where player is looking
t_ipair	c_get_player_target(const t_game *g)
{
	t_pnt	tgt;
	t_ipair	int_tgt;

	tgt.x = g->x + g->dx;
	tgt.y = g->y + g->dy;
	int_tgt.a = (int)tgt.x;
	int_tgt.b = (int)tgt.y;
	return (int_tgt);
}

void	c_player_try_open_door(const t_game *g, t_door *doors, t_uint n_doors)
{
	t_uint	i;
	t_ipair	tgt;

	tgt = c_get_player_target(g);
	i = 0;
	while (i < n_doors)
	{
		if (doors[i].x == tgt.a && doors[i].y == tgt.b)
		{
			if (doors[i].state == DOOR_CLOSED)
			{
				doors[i].state = DOOR_OPENING;
				doors[i].next_time = g->t.tv_sec * 1000 + (g->t.tv_nsec / 1e6)
					+ DOOR_PERIOD_MS;
			}
			else if (doors[i].state == DOOR_OPENED)
			{
				doors[i].state = DOOR_CLOSING;
				doors[i].next_time = g->t.tv_sec * 1000 + (g->t.tv_nsec / 1e6)
					+ DOOR_PERIOD_MS;
			}
		}
		++i;
	}
}
