/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 21:05:03 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/13 16:54:57 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d_bonus.h>

// Allocates a t_sprt and initializes it according to choice. Choice can be
// '2', '3', '4' or '5'. Outputs error message and returns NULL if error is
// encountered.
t_sprt	*c_create_sprite(t_game *g, char choice, float x, float y)
{
	t_sprt				*new_sprt;
	const t_sprt_src	*src;

	new_sprt = (t_sprt *)malloc(sizeof(t_sprt));
	if (new_sprt == NULL)
	{
		perror(strerror(errno));
		return (NULL);
	}
	src = g->c->sprt_src[choice - SPRITE_IDS[0]];
	if (src == NULL)
	{
		ft_dprintf(2, "Error\nSprite's source image isn't defined\n");
		free(new_sprt);
		return (NULL);
	}
	new_sprt->x = x;
	new_sprt->y = y;
	new_sprt->i = src->i;
	new_sprt->type = src->id;
	new_sprt->v_pos = src->v_pos;
	new_sprt->scale = src->scale;
	return (new_sprt);
}

void	c_destroy_sprite(t_sprt **sprt)
{
	free(*sprt);
	*sprt = NULL;
}
