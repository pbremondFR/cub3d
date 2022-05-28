/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_detection_utils_bonus.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 21:31:05 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/28 08:57:37 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d_bonus.h>

bool	c_is_tile_collider(const t_cub *c, int x, int y)
{
	const char	tile = c->map[y][x];
	t_door		*door;

	if (ft_strchr("0abcd", tile) && tile != '\0')
		return (false);
	else if (tile == '1')
		return (true);
	else if (tile == '-' || tile == '|')
	{
		door = c_get_door(c->doors, c->n_doors, x, y);
		if (door->state == DOOR_OPENED)
			return (false);
		else
			return (true);
	}
	else
		return (true);
}
