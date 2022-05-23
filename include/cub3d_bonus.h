/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:20:46 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/21 21:04:03 by pbremond         ###   ########.fr       */
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

typedef struct s_sprite
{
	const t_img	*i;
	t_uint		t_w; // Sprite tile's width on tilemap
	t_uint		t_h;
	const char	*addr; // Sprite's source

	float		x;
	float		y;
	float		dist_sq; // Squared distance to player
	float		scale; // Sprite's scaling factor
	char		type; // Type of sprite ('2', '3'...)
	int8_t		state; // State of sprite (for animations, AI...)
	int8_t		v_pos; // Vertical position. -1=floor, 0=floating, 1=ceiling
	void		(*routine)(t_game *, struct s_sprite *); // Function pointer for routine if needed
	long		next_time;
	t_uint		cur_tile;
	t_uint		n_tiles;
	bool		del;
}				t_sprt;

typedef struct s_sprite_source
{
	const t_img	*i;

	char		id;
	int8_t		v_pos; // Vertical position. -1=floor, 0=floating, 1=ceiling
	float		scale; // Sprite's scaling factor
	int			n_tiles; // Number of tiles
	t_uint		tile_h; // Height of one tile
}				t_sprt_src;

/*
 *              ┌────────SCREEN────────┐
 *              │                      │
 *              │                      │
 *              │                      │
 * coords_x.a   │                      │
 * coords_y.a+──┼──────+coords_x.b     │
 *           │▲ │      │               │
 *           ││ │      │               │
 *    height ││ └──────┼───────────────┘
 *           │▼        │
 * coords_y.b+─────────┘
 *           ◄─────────►
 *              width
 */

typedef struct s_sprite_disp_attributes
{
	const t_sprt	*s;
	int				screen_x;
	int				w;
	int				h;
	int				v_off;
	t_pnt			transform;
	t_ipair			coords_x; // Coordinates of the first and last X points
	t_ipair			coords_y; // Coordinates of the first and last Y points
	t_ipair			bounds_x; // Start and end of drawing zone on X axis
	t_ipair			bounds_y; // Start and end of drawing zone on Y axis
					// Reflects whether a sprite's column should be drawn or not
	bool			do_draw_x[WIN_WIDTH];
}				t_sprt_attr;

typedef struct s_door
{
	// const t_img	*i;
	int			x;
	int			y;
	long		next_time;
	int8_t		offset; // 100 = closed, 0 = opened.
	int8_t		state; // Door is closed, opened, closing, or opening
}				t_door;
# define DOOR_PERIOD_MS		10
# define DOOR_OPEN_DELTA	2
# define DOOR_OPENED		0
# define DOOR_CLOSED		2
# define DOOR_OPENING		1
# define DOOR_CLOSING		-1


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

// map_parsing_2_bonus.c
void	c_init_sprites_pos(t_game *g);

// cub_graphics_sprites_bonus.c
void	c_import_sprite(t_sprt_src **tgt_ptr, const char *line, t_game *g);

// ========================================================================== //
//                                   DOORS                                    //
// ========================================================================== //

void	c_ray_raycasting_loop_bonus(t_game *g, t_ray *ray, int8_t *offset);

bool	c_is_time_over(const struct timespec *t, long next);
void	c_move_door(t_door *door);
t_door	*c_get_door(t_door *doors, t_uint n_doors, int x, int y);
void	c_init_doors(t_cub *c);

t_ipair	c_get_player_target(const t_game *g);
void	c_player_try_open_door(const t_game *g, t_door *doors, t_uint n_doors);
void	c_doors_routine(const struct timespec *t, t_door *doors,
			t_uint n_doors);

#endif
