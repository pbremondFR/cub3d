/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_sorting_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 22:31:36 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/16 19:37:11 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d_bonus.h>

void	c_calc_sprite_dist(const t_game *g, t_list *sprt_lst)
{
	t_sprt	*sprt;

	while (sprt_lst)
	{
		sprt = (t_sprt *)sprt_lst->content;
		sprt->dist_sq = c_math_get_sq_dist(sprt->x, g->x, sprt->y, g->y);
		sprt_lst = sprt_lst->next;
	}
}

// Goes through sorted list to find correct insertion spot
static void	_insert_into_sorted(t_list *current, t_list *sorted)
{
	t_sprt	*curr_sp;

	while (sorted)
	{
		curr_sp = (t_sprt *)current->content;
		if (sorted->next == NULL
			|| curr_sp->dist_sq > ((t_sprt *)(sorted->next->content))->dist_sq)
		{
			current->next = sorted->next;
			sorted->next = current;
			return ;
		}
		sorted = sorted->next;
	}
}

t_list	*c_sort_sprites(const t_game *g, t_list *sprts_l)
{
	t_list	*sorted;
	t_list	*current;
	t_sprt	*curr_sp;

	if (sprts_l == NULL || sprts_l->next == NULL)
		return (sprts_l);
	c_calc_sprite_dist(g, sprts_l);
	sorted = NULL;
	while (sprts_l)
	{
		current = sprts_l;
		sprts_l = sprts_l->next;
		curr_sp = (t_sprt *)current->content;
		if (sorted == NULL
			|| curr_sp->dist_sq > ((t_sprt *)(sorted->content))->dist_sq)
			ft_lstadd_front(&sorted, current);
		else
			_insert_into_sorted(current, sorted);
	}
	return (sorted);
}
