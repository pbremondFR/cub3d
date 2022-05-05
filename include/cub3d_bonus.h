/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:20:46 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/05 16:26:15 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <cub3d.h>

// # define FONT_PATH		"./assets/charmap_zoom2x.xpm"
// # define FONT_BM_W		18
// # define FONT_BM_H		7
// # define FONT_OFFSET	-32
// # define FONT_PATH		"./assets/cub3d_font_bitmap_comic_sans.xpm"
// # define FONT_BM_W		16
// # define FONT_BM_H		8
// # define FONT_OFFSET	0
# define FONT_PATH		"./assets/cub3D_font_bitmap_2x.xpm"
# define FONT_BM_W		16
# define FONT_BM_H		8
# define FONT_OFFSET	0

# define DBOX_TOP_OUTLINE	"\x09\x0f\x0b"
# define DBOX_BOT_OUTLINE	"\x0c\x0f\x0e"
# define SBOX_TOP_OUTLINE	"\x01\x07\x03"
# define SBOX_BOT_OUTLINE	"\x04\x07\x06"

# define MINIMAP_TILE_SIZ		11
# define MM_TIL_SIZ				MINIMAP_TILE_SIZ
# define MINIMAP_WIDTH			13
# define MINIMAP_HEIGHT			9

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
void	c_putstr_to_frame_dbox(t_game *g, t_ipair coord, int color,
			const char *str);
void	c_putstr_to_frame_sbox(t_game *g, t_ipair coord, int color,
			const char *str);

void	c_draw_square(t_img *img, t_ipair coord, t_ipair colors, int size);
void	c_draw_square_2(t_img *img, t_ipair coord, uint64_t col, int size);

void	c_minimap_render(t_game *g, int x, int y);

#endif
