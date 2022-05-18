/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 18:54:51 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/18 18:57:04 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d_bonus.h>

bool	c_is_time_over(const struct timespec *t, long next)
{
	return (t->tv_sec * 1000 + (t->tv_nsec / 1e6) > next);
}
