/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event_handlers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:04:38 by pbremond          #+#    #+#             */
/*   Updated: 2024/12/17 16:07:28 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	c_mousepress_handler(int key, int x, int y, void *handle)
{
	t_game	*g;

	(void)x;
	(void)y;
	g = (t_game *)handle;
	if (key == KEYC_M1)
		g->k |= KEYS_M1;
	else if (key == KEYC_M2)
		g->k |= KEYS_M2;
	else if (key == KEYC_M3)
		g->k |= KEYS_M3;
	return (0);
}

int	c_mouserelease_handler(int key, int x, int y, void *handle)
{
	t_game	*g;

	(void)x;
	(void)y;
	g = (t_game *)handle;
	if (key == KEYC_M1)
		g->k ^= KEYS_M1;
	else if (key == KEYC_M2)
		g->k ^= KEYS_M2;
	else if (key == KEYC_M3)
		g->k ^= KEYS_M3;
	return (0);
}
