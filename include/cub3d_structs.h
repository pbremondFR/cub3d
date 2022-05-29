/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 01:51:14 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/29 05:53:29 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRUCTS_H
# define CUB3D_STRUCTS_H

# include <stdlib.h>
# include <cub3d.h>

// ========================================================================== //
//                                  STRUCTS                                   //
// ========================================================================== //

typedef unsigned int			t_uint;
typedef struct s_list			t_list;

typedef struct s_point
{
	float	x;
	float	y;
}				t_pnt;

typedef struct s_int_pair
{
	int	a;
	int	b;
}				t_ipair;

/*! @struct s_raycast
 *  @brief This structure contains everything needed by the DDA raycasting
 *  algorithm, drawing functions, etc. It represents a single ray.
 *  @var s_raycast::dir_x
 *   Represents the ray's direction vector. This vector is normalized.
 *  @var s_raycast::dir_y
 *   Represents the ray's direction vector. This vector is normalized.
 *  @var s_raycast::delta_dist_x
 *   How much should the ray step in the X direction.
 *  @var s_raycast::delta_dist_y
 *   How much should the ray step in the Y direction.
 *  @var s_raycast::len_x
 *   Length of ray until collision on X axis.
 *  @var s_raycast::len_y
 *   Length of ray until collision on Y axis.
 *  @var s_raycast::c_plane_len
 *   Final length of ray, adjusted for fisheye.
 *  @var s_raycast::map_x
 *   Ray's X position in map
 *  @var s_raycast::map_y
 *   Ray's Y position in map
 *  @var s_raycast::step_x
 *   Ray's stepping direction in the X axis. Is always 1 or -1.
 *  @var s_raycast::step_y
 *   Ray's stepping direction in the Y axis. Is always 1 or -1.
 *  @var s_raycast::side
 *   What axis did collision occur on ? Is either WALL_HIT_X or WALL_HIT_Y
 */
typedef struct s_raycast
{
	float	dir_x;
	float	dir_y;
	float	delta_dist_x;
	float	delta_dist_y;
	float	len_x;
	float	len_y;
	float	c_plane_len;
	int		map_x;
	int		map_y;
	int8_t	step_x;
	int8_t	step_y;
	int8_t	side;
}				t_ray;

/*! @struct s_mlx_img
 *  @brief This structure represents an MLX image. For more information
 *  on what each member does, seek MLX documentation.
 *  @var s_mlx_img::*i
 *   MLX image handle.
 *  @var s_mlx_img::*addr
 *   Image buffer, represented as a contiguous char array.
 *  @var s_mlx_img::bpp
 *   Image's bits-per-pixel. 32 in our case, thus, a pixel can be represented
 *   by an int32.
 *  @var s_mlx_img::ls
 *   Image's line size, in bytes.
 *  @var s_mlx_img::e
 *   Image's endian type. 0 for little endian, 1 for big endian.
 *  @var s_mlx_img::w
 *   Image width.
 *  @var s_mlx_img::h
 *   Image height.
 */
typedef struct s_mlx_img
{
	void	*i;
	char	*addr;

	int		bpp;
	int		ls;
	int		e;

	int		w;
	int		h;
}				t_img;

# define SPRITE_MAX_NUM	4

/*! @struct s_cub_data
 *  @brief This structure contains all necessary information provided by
 *  the .cub file.
 *  @var s_cub_data::**map
 *   2D array representing the given .cub map.
 *  @var s_cub_map::sx
 *   Map's X size (width).
 *  @var s_cub_map::sy
 *   Map's Y size (height).
 *  @var s_cub_map::*n
 *   Texture to apply to north facing walls. Pattern repeast for South, East,
 *   West, and door textures.
 *  @var s_cub_map::*font
 *   Font bitmap to be used in-game.
 *  @var s_cub_map::f
 *   Colour to be used as floor colour. Same goes for `c', the ceiling color.
 *  @var s_cub_map::*sprt_src
 *   Array containing sprite sources.
 *  @var s_cub_map::sprt_src_id
 *   Array containing an ID for each sprite in the source.
 *   e.g, src[0] has ID 'b', src[1] has ID 'a', src[2] has ID 'c'...
 *  @var s_cub_map::*doors
 *   An array containing every door in the map.
 *  @var s_cub_map::n_doors
 *   How many doors there are in the map.
 */
typedef struct s_mlx_font		t_font;
typedef struct s_sprite_source	t_sprt_src;
typedef struct s_door			t_door;
typedef struct s_cub_data
{
	char		**map;
	t_uint		sx;
	t_uint		sy;

	t_img		*n;
	t_img		*s;
	t_img		*e;
	t_img		*w;
	t_font		*font;
	t_img		*door;

	int			f;
	int			c;

	t_sprt_src	*sprt_src[SPRITE_MAX_NUM];
	char		sprt_src_id[SPRITE_MAX_NUM];
	t_door		*doors;
	t_uint		n_doors;
}				t_cub;

t_cub		*c_init_t_cub(t_cub *p_cub);

/*! @struct s_game_data
 *  @brief This structure contains all variables necessary to the game when
 *  running. All X and Y parameters will only be mentioned once, for brevity.
 *  @var s_game_data::x
 *   Player's X position
 *  @var s_game_data::vx
 *   Player's velocity. X for left/right (strafing), Y for back and forth.
 *  @var s_game_data::va
 *   Player head's angular velocity.
 *  @var s_game_data::dx
 *   Player's direction vector.
 *  @var s_game_data::cx
 *   Player's camera plane vector.
 *  @var s_game_data::k
 *   A 16 bit int with every bit representing the boolean state of an X11 key.
 *  @var s_game_data::m_cap
 *   A boolean representing whether or not mouse look (and capture) is enabled.
 *  @var s_game_data::*c
 *   Pointer to s_cub_data structure.
 *  @var s_game_data::f
 *   s_mlx_img structure of the frame displayed on screen.
 *  @var s_game_data::*mlx
 *   MLX handle.
 *  @var s_game_data::*mw
 *   MLX window handle.
 *  @var s_game_data::olay
 *   s_mlx_img structure for the minimap, which can be overlayed on top of
 *   the current frame.
 *  @var s_game_data::*sprts_lst
 *   Linked list of every sprite present in the game.
 *  @var s_game_data::n_sprt
 *   Number of sprites present in the game.
 *  @var s_game_data::t
 *   struct timespec for in-game timer.
 */
typedef struct s_game_data
{
	float			x;
	float			y;
	float			vx;
	float			vy;
	float			va;
	float			dx;
	float			dy;
	float			cx;
	float			cy;

	uint16_t		k;
	char			m_cap;

	t_cub			*c;

	t_img			f;

	void			*mlx;
	void			*mw;

	t_img			olay;
	t_list			*sprts_lst;
	uint8_t			n_sprt;
	struct timespec	t;
}				t_game;
t_game		*c_init_t_game(t_game *g);

// ========================================================================== //
//                               BONUS STRUCTS                                //
// ========================================================================== //

/*! @struct s_mlx_font
 *  @brief This structure represents a font bitmap. All parameters are identical
 *  to a s_mlx_img except the ones described here.
 *  @var s_mlx_font::bm_w
 *   Bitmap width: how many characters there are per line. Same goes for bm_h.
 *  @var s_mlx_font::offset
 *   An ASCII offset to be applied to bitmaps which aren't ASCII compliant
 *   (e.g. starting at ASCII 32 instead of ASCII 0).
 *  @var s_mlx_font::c_w
 *   Each character's width, in pixels. Same goes for c_h.
 */
typedef struct s_mlx_font
{
	void	*i;
	char	*addr;

	int		bpp;
	int		ls;
	int		e;

	int		i_w;
	int		i_h;

	char	bm_w;
	char	bm_h;
	char	offset;

	int		c_w;
	int		c_h;
}				t_font;

/*! @struct s_mlx_font
 *  @brief This structure represents a font bitmap. All parameters are identical
 *  to a s_mlx_img except the ones described here.
 *  @var s_sprite::*i
 *   Pointer to sprite's t_img source texture.
 *  @var s_sprite::t_w
 *   Width in pixel of a sprite's tile in tilemap. Warning: sprite tilemaps were
 *   ONLY made for a vertical arrangement. Thus, this value always equals the
 *   source's texture's width.
 *  @var s_sprite::t_h
 *   Height in pixels of a sprite's height in tilemap.
 *  @var s_sprite::*addr
 *   MLX data address buffer to look into. This pointer can be changed to point
 *   to a different part of the texture, to make animations possible.
 *  @var s_sprite::x
 *   Sprite's X position in the world. Can be edited when playing. Same for Y.
 *  @var s_sprite::dist_sq
 *   Sprite's squared distance to the player. For sprite sorting.
 *  @var s_sprite::type
 *   Type of sprite, according to SPRITE_IDS.
 *  @var s_sprite::state
 *   To be freely used with sprite routines.
 *  @var s_sprite::v_pos
 *   Vertical position of sprite. -1=floor, 0=hovering, 1=ceiling. Doesn't work.
 *  @var s_sprite::*routine
 *   Function pointer to the sprite's animation routine. Defaults to
 *   c_sprite_default_animate_routine(), but can be changed for custom sprites.
 *  @var s_sprite::next_time
 *   In milliseconds since epoch. Represents when next animation will be played.
 *  @var s_sprite::cur_tile
 *   Represents what tile from sprite's tilemap is currently displayed.
 *  @var s_sprite::n_tiles
 *   How many tiles there are in sprite's tilemap.
 *  @var s_sprite::del
 *   When true, queues up this sprite instance for deletion.
 */
typedef struct s_sprite
{
	const t_img	*i;
	t_uint		t_w;
	t_uint		t_h;
	const char	*addr;

	float		x;
	float		y;
	float		dist_sq;
	float		scale;
	char		type;
	int8_t		state;
	int8_t		v_pos;
	void		(*routine)(t_game *, struct s_sprite *);
	long		next_time;
	t_uint		cur_tile;
	t_uint		n_tiles;
	bool		del;
}				t_sprt;

/*! @struct s_sprite_source
 *  @brief This structure represents a source for a sprite type. When
 *  instanciating the sprite, data will be fetched in appropriate source.
 *  @var s_sprite_source::*i
 *   Pointer to sprite's texture MLX image.
 *  @var s_sprite_source::id
 *   Sprite's ID, in accordance with SPRITE_IDS.
 *  @var s_sprite_source::v_pos
 *   Vertical position of sprite. -1=floor, 0=hovering, 1=ceiling. Doesn't work.
 *  @var s_sprite_source::n_tiles
 *   Number of tiles in sprite's tilemap.
 *  @var s_sprite_source::tile_h
 *   In pixels, height of one tile in tilemap.
 */
typedef struct s_sprite_source
{
	const t_img	*i;

	char		id;
	int8_t		v_pos;
	float		scale;
	int			n_tiles;
	t_uint		tile_h;
}				t_sprt_src;

/*! @struct s_sprite_disp_attributes
 *  @brief This structure holds all necessary information for sprite rendering.
 *  @var s_sprite_disp_attributes::screen_x
 *   Sprite's X coordinate on the screen.
 *  @var s_sprite_disp_attributes::w
 *   Sprite's width on screen. Same goes for height.
 *  @var s_sprite_disp_attributes::v_off
 *   Vertical position of sprite. -1=floor, 0=hovering, 1=ceiling. Doesn't work.
 *  @var s_sprite_disp_attributes::transform
 *   X and Y tranformations from matrix calculation.
 *  @var s_sprite_disp_attributes::coords_x
 *   Coordinates of the first and last X points. Same goes for Y.
 *  @var s_sprite_disp_attributes::coords_y
 *   Start and end of drawing zone on X axis. Same goes for Y.
 *  @var s_sprite_disp_attributes::do_draw_x
 *   Reflects whether a sprite's column should be drawn or not.
 */
typedef struct s_sprite_disp_attributes
{
	const t_sprt	*s;
	int				screen_x;
	int				w;
	int				h;
	int				v_off;
	t_pnt			transform;
	t_ipair			coords_x;
	t_ipair			coords_y;
	t_ipair			bounds_x;
	t_ipair			bounds_y;
	bool			do_draw_x[WIN_WIDTH];
}				t_sprt_attr;

# define DOOR_PERIOD_MS		10
# define DOOR_OPEN_DELTA	2
# define DOOR_OPENED		0
# define DOOR_CLOSED		2
# define DOOR_OPENING		1
# define DOOR_CLOSING		-1

/*! @struct s_door
 *  @brief This structure represents a door.
 *  @var s_door::x
 *   Door's X position. Do NOT edit. Same for Y.
 *  @var s_door::next_time
 *   In milliseconds from Epoch. Represents when door will be moved again.
 *  @var s_door::offset
 *   Door's offset, for rendering. 100 = fully closed, 0 = fully opened.
 *  @var s_door::state
 *   Door's state. Opened/Closed/Opening/Closing. Change this value to move
 *   the door, not the offset directly.
 */
typedef struct s_door
{
	const int	x;
	const int	y;
	long		next_time;
	int8_t		offset;
	int8_t		state;
}				t_door;

#endif
