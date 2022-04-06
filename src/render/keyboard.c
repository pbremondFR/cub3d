/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:26:21 by pbremond          #+#    #+#             */
/*   Updated: 2022/04/06 15:26:41 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

int	c_keypress_handler(int key, void *handle)
{
	t_game	*g;

	g = (t_game *)handle;
	if (key == KEYC_W)
		g->k |= KEYS_W;
	if (key == KEYC_S)
		g->k |= KEYS_S;
	if (key == KEYC_D)
		g->k |= KEYS_D;
	if (key == KEYC_A)
		g->k |= KEYS_A;
	if (key == KEYC_ESC)
		g->k |= KEYS_ESC;
	return (0);
}

int	c_keyrelease_handler(int key, void *handle)
{
	t_game	*g;

	g = (t_game *)handle;
	if (key == KEYC_W)
		g->k ^= KEYS_W;
	if (key == KEYC_S)
		g->k ^= KEYS_S;
	if (key == KEYC_D)
		g->k ^= KEYS_D;
	if (key == KEYC_A)
		g->k ^= KEYS_A;
	if (key == KEYC_ESC)
		g->k ^= KEYS_ESC;
	return (0);
}
