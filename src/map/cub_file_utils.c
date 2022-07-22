/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_file_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 10:04:18 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/28 10:09:55 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <libft.h>

// Initializes all members of t_cub. If p_cub is NULL, mallocs a t_cub and
// returns it.
t_cub	*c_init_t_cub(t_cub *p_cub)
{
	t_cub	*cub;

	if (p_cub)
		cub = p_cub;
	else
		cub = (t_cub *)malloc(sizeof(t_cub));
	cub->map = NULL;
	cub->sx = 0;
	cub->sy = 0;
	cub->n = NULL;
	cub->s = NULL;
	cub->e = NULL;
	cub->w = NULL;
	cub->door = NULL;
	cub->f = -1;
	cub->c = -1;
	ft_memset(cub->sprt_src, '\0', sizeof(uintptr_t) * SPRITE_MAX_NUM);
	ft_memset(cub->sprt_src_id, '\0', sizeof(char) * SPRITE_MAX_NUM);
	return (cub);
}

int	c_cub_try_open_file(const char *path)
{
	int			fd;
	const char	*last_4;

	last_4 = path + (ft_strlen(path) - ft_stmin(ft_strlen(path), 4));
	if (ft_strncmp(last_4, ".cub", 4) != 0)
	{
		ft_dprintf(2, "Error\nExpected `*.cub' file, got `%s'\n", path);
		return (-1);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_dprintf(2, "Error\nCouldn't open %s: %s\n", path, strerror(errno));
		return (-1);
	}
	return (fd);
}
