/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:20:46 by pbremond          #+#    #+#             */
/*   Updated: 2022/04/29 22:06:11 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <cub3d.h>

# define FONT_PATH		"./assets/charmap.xpm"
# define FONT_BM_W		18
# define FONT_BM_H		7
# define FONT_OFFSET	-32

typedef struct s_mlx_font
{
	void	*i; // Image handle
	char	*addr; // Char buffer to write into

	int		bpp; // Bits per pixel
	int		ls; // Line size
	int		e; // Endian
	
	int		i_w; // Image width
	int		i_h; // Image height

	char	bm_w; // Bitmap width
	char	bm_h; // Bitmap height
	char	offset; // ASCII offset to apply in bitmap

	int		c_w; // Char width
	int		c_h; // Char height
}				t_font;

void	c_load_font(t_game *g);
void	c_putstr_to_frame(t_game *g, t_ipair coord, int color, const char *str);

#endif
