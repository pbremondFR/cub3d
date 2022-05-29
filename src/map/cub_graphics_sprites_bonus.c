/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_graphics_sprites_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 03:06:55 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/29 05:46:39 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d_bonus.h>

static void	_fatal_exit(void)
{
	write(2, "Fatal error: ", 13);
	perror(strerror(errno));
	exit(errno);
}

static int	_parse_values(t_sprt_src *tgt, char id)
{
	tgt->id = id;
	if (tgt->scale <= 0.0f)
	{
		ft_dprintf(2, "Error\nIllegal sprite scale value\n");
		return (EXIT_FAILURE);
	}
	if (tgt->v_pos == 'F')
		tgt->v_pos = -1;
	else if (tgt->v_pos == 'N')
		tgt->v_pos = 0;
	else if (tgt->v_pos == 'C')
		tgt->v_pos = 1;
	else
	{
		ft_dprintf(2, "Error\nIllegal sprite height value\n");
		return (EXIT_FAILURE);
	}
	if (tgt->n_tiles <= 0 || tgt->n_tiles > 255)
	{
		ft_dprintf(2, "Error\nIllegal number of tiles provided");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

// NOTE: If porting this code, remember to change the sscanf string limit !
void	c_import_sprite(t_sprt_src **tgt_ptr, const char *line, t_game *g)
{
	t_sprt_src	*tgt;
	char		path[PATH_MAX + 1];

	if (*tgt_ptr != NULL)
	{
		ft_dprintf(2, "Error\nRedefined `%c' sprite texture.\n", line[-1]);
		c_exit_program(g, 1);
	}
	*tgt_ptr = (t_sprt_src *)malloc(sizeof(t_sprt_src));
	if (*tgt_ptr == NULL)
		_fatal_exit();
	tgt = *tgt_ptr;
	if (sscanf(line, "%1024s %f %c %d", path, &tgt->scale, &tgt->v_pos,
			&tgt->n_tiles) != 4 || _parse_values(tgt, line[-1]) != EXIT_SUCCESS)
	{
		ft_dprintf(2, "Error\nIncorrect `%c' sprite definition\n", line[-1]);
		c_exit_program(g, 1);
	}
	tgt->i = c_import_xpm(path, g, false);
	if (tgt->i == NULL)
		c_exit_program(g, 1);
	tgt->tile_h = tgt->i->h / tgt->n_tiles;
}
