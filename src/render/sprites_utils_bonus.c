/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 21:05:03 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/13 19:42:26 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d_bonus.h>

static void	_init_new_values(t_sprt *new_sprt, const t_sprt_src *src)
{
	new_sprt->i = src->i;
	new_sprt->v_pos = src->v_pos;
	new_sprt->scale = src->scale;
	new_sprt->state = 0;
	new_sprt->n_tiles = src->n_tiles;
	if (new_sprt->n_tiles == 1)
		new_sprt->routine = NULL;
	else if (new_sprt->type == 'b')
		new_sprt->routine = &c_barrel_animate_routine;
	else
		new_sprt->routine = &c_sprite_default_animate_routine;
	new_sprt->t_w = new_sprt->i->w;
	new_sprt->t_h = src->tile_h;
	new_sprt->addr = new_sprt->i->addr;
	new_sprt->skip = false;
}

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
	new_sprt->type = src->id;
	new_sprt->next_time = g->t.tv_sec;
	_init_new_values(new_sprt, src);
	return (new_sprt);
}

void	c_destroy_sprite(t_sprt **sprt)
{
	free(*sprt);
	*sprt = NULL;
}

// Default animation routine. Cycles through all tilemap's tiles, one each 0.3s
void	c_sprite_default_animate_routine(t_game *g, t_sprt *sprt)
{
	if (g->t.tv_sec * 1000 + (g->t.tv_nsec / 1e6) < sprt->next_time)
		return ;
	sprt->cur_tile += 1;
	if (sprt->cur_tile >= sprt->n_tiles)
		sprt->cur_tile = 0;
	sprt->addr = c_get_const_target_addr(sprt->i, 0,
			sprt->cur_tile * sprt->t_h);
	sprt->next_time = g->t.tv_sec * 1000 + (g->t.tv_nsec / 1e6 + 500);
}

void	c_barrel_animate_routine(t_game *g, t_sprt *sprt)
{
	if (g->t.tv_sec * 1000 + (g->t.tv_nsec / 1e6) < sprt->next_time)
		return ;
	if (sprt->state == 0 && fabsf(c_math_get_sq_dist(sprt->x, g->x, sprt->y, g->y)) < 1.0f)
		sprt->state = 1;
	sprt->cur_tile += 1;
	if (sprt->state == 0)
	{
		if (sprt->cur_tile >= 3)
			sprt->cur_tile = 0;
		sprt->addr = c_get_const_target_addr(sprt->i, 0,
				sprt->cur_tile * sprt->t_h);
		sprt->next_time = g->t.tv_sec * 1000 + (g->t.tv_nsec / 1e6 + 500);
	}
	else
	{
		if (sprt->state == 1)
			sprt->cur_tile = 4;
		sprt->state = 2;
		if (sprt->cur_tile >= sprt->n_tiles)
		{
			g->c->map[(int)sprt->y][(int)sprt->x] = '0';
			sprt->skip = true;
		}
		else
		{
			sprt->addr = c_get_const_target_addr(sprt->i, 0,
					sprt->cur_tile * sprt->t_h);
			sprt->next_time = g->t.tv_sec * 1000 + (g->t.tv_nsec / 1e6 + 110);
		}
	}
}
