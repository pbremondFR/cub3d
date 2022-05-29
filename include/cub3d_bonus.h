/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:20:46 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/29 08:22:19 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <cub3d.h>
# include <time.h>
# include <sys/time.h>

# define CLOCKS_PER_MS	1000

# undef MAP_LEGAL_CHARS
# define MAP_LEGAL_CHARS	"01NESW abcd-|"

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
# define MINIMAP_BORDER_SIZE	4
# define MM_BORD_SIZ			MINIMAP_BORDER_SIZE

// ========================================================================== //
//                                   MISC                                     //
// ========================================================================== //

// raycast_bonus.c
void	c_ray_raycasting_loop_bonus(t_game *g, t_ray *ray, int8_t *offset);

// utils_bonus.c
bool	c_is_time_over(const struct timespec *t, long next);

// ========================================================================== //
//                                CUSTOM FONT                                 //
// ========================================================================== //

void	c_load_font(t_game *g);
void	c_putstr_to_frame(t_game *g, t_ipair coord, int color, const char *str);
void	c_putstr_to_frame_dbox(t_game *g, t_ipair coord, int color,
			const char *str);
void	c_putstr_to_frame_sbox(t_game *g, t_ipair coord, int color,
			const char *str);

// ========================================================================== //
//                                  MINIMAP                                   //
// ========================================================================== //

// minimap_bonus.c
void	c_minimap_render(t_game *g, int x, int y);

// ========================================================================== //
//                                  SPRITES                                   //
// ========================================================================== //

// sprites_bonus.c
t_pnt	c_sprite_projection_matrix(float sprite_x, float sprite_y,
			const t_game *g);
void	c_render_sprites(t_game *g, t_list *sprts_lst, float ray_len_buf[]);

// sprites_sorting_bonus.c
void	c_calc_sprite_dist(const t_game *g, t_list *sprt_lst);
t_list	*c_sort_sprites(const t_game *g, t_list *p_sprt_lst);

// sprites_utils_bonus.c
t_sprt	*c_create_sprite(t_game *g, char choice, float x, float y);
void	c_destroy_sprite(t_sprt **sprt);
void	c_sprite_default_animate_routine(t_game *g, t_sprt *sprt);
void	c_barrel_animate_routine(t_game *g, t_sprt *sprt);

// map_parsing_bonus.c
void	c_init_sprites_pos(t_game *g);

// cub_graphics_sprites_bonus.c
void	c_import_sprite(t_sprt_src **tgt_ptr, const char *line, t_game *g);

// ========================================================================== //
//                                   DOORS                                    //
// ========================================================================== //

// doors_bonus.c
void	c_move_door(t_door *door);
t_door	*c_get_door(t_door *doors, t_uint n_doors, int x, int y);
void	c_doors_routine(const struct timespec *t, t_door *doors,
			t_uint n_doors);
t_ipair	c_get_player_target(const t_game *g);
void	c_player_try_open_door(const t_game *g, t_door *doors, t_uint n_doors);

// map_parsing_bonus.c
void	c_init_doors(t_cub *c);

#endif
