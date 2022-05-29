/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font_display_bonus_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:54:00 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/29 04:02:51 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d_bonus.h>

static void	_get_box_outline_str(char *str, const char *chrset, int n)
{
	int	i;

	i = 0;
	str[i++] = *chrset++;
	while (i < n - 1)
		str[i++] = *chrset;
	if (i < n)
		str[i++] = *(++chrset);
}

void	c_putstr_to_frame_dbox(t_game *g, t_ipair coord, int color,
	const char *str)
{
	size_t	init_len;
	char	*edited_str;

	init_len = ft_strlen(str);
	edited_str = malloc(((init_len + 2) + 1) * sizeof(char));
	if (edited_str == NULL)
		c_fatal_exit();
	edited_str[init_len + 2] = '\0';
	_get_box_outline_str(edited_str, DBOX_TOP_OUTLINE, init_len + 2);
	c_putstr_to_frame(g, coord, color, edited_str);
	coord.b += g->c->font->c_h;
	edited_str[0] = '\x10';
	ft_strncpy(edited_str + 1, str, init_len);
	edited_str[init_len + 1] = '\x10';
	c_putstr_to_frame(g, coord, color, edited_str);
	coord.b += g->c->font->c_h;
	_get_box_outline_str(edited_str, DBOX_BOT_OUTLINE, init_len + 2);
	c_putstr_to_frame(g, coord, color, edited_str);
	free(edited_str);
}

void	c_putstr_to_frame_sbox(t_game *g, t_ipair coord, int color,
	const char *str)
{
	size_t	init_len;
	char	*edited_str;

	init_len = ft_strlen(str);
	edited_str = malloc(((init_len + 2) + 1) * sizeof(char));
	if (edited_str == NULL)
		c_fatal_exit();
	edited_str[init_len + 2] = '\0';
	_get_box_outline_str(edited_str, SBOX_TOP_OUTLINE, init_len + 2);
	c_putstr_to_frame(g, coord, color, edited_str);
	coord.b += g->c->font->c_h;
	edited_str[0] = '\x08';
	ft_strncpy(edited_str + 1, str, init_len);
	edited_str[init_len + 1] = '\x08';
	c_putstr_to_frame(g, coord, color, edited_str);
	coord.b += g->c->font->c_h;
	_get_box_outline_str(edited_str, SBOX_BOT_OUTLINE, init_len + 2);
	c_putstr_to_frame(g, coord, color, edited_str);
	free(edited_str);
}
