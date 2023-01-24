/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 18:54:51 by pbremond          #+#    #+#             */
/*   Updated: 2023/01/16 19:38:42 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d_bonus.h>

bool	c_is_time_over(const struct timespec *t, long next)
{
	return (t->tv_sec * 1000 + (t->tv_nsec / 1e6) > next);
}

// Checks for escape, toggles mouse look, tries to open door
void	c_check_keys(t_game *g)
{
	if (g->k == KEYS_ESC)
		c_exit_program(g, 0);
	if (g->m_cap)
		c_mouse_look(g);
	if (g->k & (KEYS_M1 | KEYS_UP))
		c_player_try_open_door(g, g->c->doors, g->c->n_doors);
}
