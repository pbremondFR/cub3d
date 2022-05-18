/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 20:46:15 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/18 21:17:39 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d_bonus.h>

// Changes how much door is opened/closed by DOOR_OPEN_DELTA.
// door->state has to be +1 or -1, corresponding to an opening or a closing.
void	c_move_door(t_door *door)
{
	door->open += DOOR_OPEN_DELTA * door->state;
	if (door->open <= 0)
	{
		door->state = DOOR_CLOSED;
		door->open = 0;
	}
	else if (door->open >= 100)
	{
		door->state = DOOR_OPENED;
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
