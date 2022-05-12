/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 20:43:01 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/12 01:47:34 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include <math.h>

# include <stdbool.h>

# include "ansi_color.h"
# include "mlx.h"

# define MAP_LEGAL_CHARS	"01NESW "
# define M_CHRS				MAP_LEGAL_CHARS

# define SPRITE_CHARS		"2345"

# define EVENT_KEY_DOWN			2
# define EVENT_KEY_UP			3
# define EVENT_SCROLL_DOWN		4
# define EVENT_SCROLL_UP		5
# define EVENT_MOUSE_MOVE		6
# define EVENT_EXPOSE			12
# define EVENT_DESTROY			17

# define E_KDWN		EVENT_KEY_DOWN
# define E_KUP		EVENT_KEY_UP
# define E_MDWN		EVENT_SCROLL_DOWN
# define E_MUP		EVENT_SCROLL_UP
# define E_MMOV		EVENT_MOUSE_MOVE
# define E_XP		EVENT_EXPOSE
# define E_DSTR		EVENT_DESTROY

# define KEYC_ESC	53
# define KEYC_W		13
# define KEYC_A		0
# define KEYC_S		1
# define KEYC_D		2
# define KEYC_LEFT	123
# define KEYC_RIGHT	124
# define KEYC_SPA	49

# define KEYS_A		0x0001
# define KEYS_S		0x0002
# define KEYS_D		0x0004
# define KEYS_W		0x0008
# define KEYS_LEFT	0x0010
# define KEYS_RIGHT	0x0020
# define KEYS_SPA	0x0040
# define KEYS_ESC	0x0080

# define KEYS_M1	0x0100
# define KEYS_M2	0x0200
# define KEYS_M3	0x0400
# define KEYS_MUP	0x0800
# define KEYS_MDNW	0x1000

# define WIN_WIDTH		720
# define WIN_HEIGHT		540
# define WIN_FWIDTH		(float)WIN_WIDTH
# define WIN_FHEIGHT	(float)WIN_HEIGHT
// # define CAM_WIDTH		720
// # define CAM_HEIGHT		440
// # define CAM_FWIDTH		(float)CAM_WIDTH
// # define CAM_FHEIGHT	(float)CAM_HEIGHT

# define ACCEL			0.005f
# define DECEL			0.003f
# define MAX_VEL		0.075f
# define ANG_VEL_ACC	0.005f
# define ANG_VEL_DEC	0.008f
# define ANG_VEL_MAX	0.05f
# define MOUSE_SENS		0.003f

# define RAY_HIT_X	0
# define RAY_HIT_Y	1

# define PLAYER_FOV	0.66f

// ========================================================================== //
//                                  STRUCTS                                   //
// ========================================================================== //

typedef unsigned int		t_uint;

typedef struct s_point
{
	float	x;
	float	y;
}				t_pnt;

typedef struct s_raycast
{
	float	dir_x; // Ray's direction vector
	float	dir_y;
	float	delta_dist_x; // Ray stepping distance
	float	delta_dist_y;
	float	len_x; // Length of ray until next vertical wall
	float	len_y; // Length of ray until next horizontal wall
	float	c_plane_len; // Final length of ray, adjusted for fisheye
	int		map_x; // Initial ray position in map
	int		map_y;
	int8_t	step_x; // Raycasting direction (pos/neg)
	int8_t	step_y;
	// int8_t	hit;
	int8_t	side; // What wall side did ray hit (x/y)
}				t_ray;

typedef struct s_mlx_img
{
	void	*i; // Image handle
	char	*addr; // Char buffer to write into

	int		bpp; // Bits per pixel
	int		ls; // Line size
	int		e; // Endian
	
	int		w; // Image width
	int		h; // Image height
}				t_img;

# define SPRITE_MAX_NUM	4

typedef struct s_mlx_font	t_font;
typedef struct s_cub_data
{
	char	**map;
	t_uint	sx; // Map x max size
	t_uint	sy; // Map y max size

	t_img	*n; // North texture
	t_img	*s; // South texture
	t_img	*e; // East texture
	t_img	*w; // West texture
	t_font	*font; // Font bitmap
	
	int		f; // Floor
	int		c; // Ceiling

	t_img	*sprt_src[SPRITE_MAX_NUM];
	char	sprt_src_id[SPRITE_MAX_NUM];

	// int		pl_x; // Player start position
	// int		pl_y;
}				t_cub;

t_cub		*c_init_t_cub(t_cub *p_cub);

typedef struct s_list		t_list;

// typedef struct s_sprite		t_sprt;

typedef struct s_game_data
{
	float		x; // Player x position
	float		y; // Player y position
	float		vx; // Player x velocity
	float		vy; // Player y velocity
	float		va; // Player head's angular velocity
	float		dx; // Player direction vector's x
	float		dy; // Player direction vector's y
	float		cx; // Player camera plane's x
	float		cy; // Player camera plane's y

	uint16_t	k; // Keystate
	char		m_cap; // Mouse capture boolean

	t_cub		*c; // .cub file data

	t_img		f; // MLX image for frame

	void		*mlx; // MLX handle
	void		*mw; // MLX window

	t_img		olay; // Overlay MLX image (minimap)
	t_list		*sprts_lst; // Sprites list
	uint8_t		n_sprt;
}				t_game;
t_game		*c_init_t_game(t_game *g);

// ========================================================================== //
//                                  MAIN/MISC                                 //
// ========================================================================== //

// keyboard.c
int			c_keypress_handler(int key, void *handle);
int			c_keyrelease_handler(int key, void *handle);
// mouse.c
void		c_toggle_mouselook(t_game *g);
void		c_mouse_look(t_game *g);

// utils.c
int			c_exit_program(void *g_handle);

// ========================================================================== //
//                                  CUB FILE                                  //
// ========================================================================== //

// checking_funcs.c
int			str_isspace(const char *line);
int			c_is_flooradj_legal(const char c);
size_t		ft_stmin(size_t a, size_t b);

// cub_graphics.c
char		**c_xpm_to_char(const char *path);
t_img		*c_import_xpm(const char *line, t_game *g, bool opt);
int			c_parse_color(const char *line);

// cub_graphics_2.c
int			c_opt_texture_for_cache(t_img *img);
int			c_opt_texture_for_cache_2(t_img *img, t_game *g);

// cub_file.c
t_cub		*c_parse_cub_file(const char *path, t_cub *c, t_game *g);

// cub_file_processing.c
int			c_cub_process_line(const char *line, t_cub *c, t_game *g);

// map_parsing.c
void		c_parse_map(const char *first_line, int fd, t_cub *c);
void		c_init_player_pos(t_game *g, t_cub *c);

// map_error_check.c
int			c_map_error_check(const char **map);

// map_print.c
void		c_map_print_error(const char **map, unsigned int x, unsigned int y);

// ========================================================================== //
//                                   RENDER                                   //
// ========================================================================== //

typedef struct s_int_pair
{
	int	a;
	int	b;
}				t_ipair;

typedef struct s_texture_line
{
	const char	*addr;
	int			ls;
	int			w;
}				t_tex_line;

// movement.c
void		c_move_player(t_game *g);
void		c_collision_handling(t_game *g, float next_x, float next_y);
void		c_player_decel(float *vx, float *vy, float *va, int keystate);

// rendering.c
int			c_render(void *handle);
// void		c_render_raycast_loop(t_game *g);

// textures.c
void		c_start_draw_wall(t_game *g, t_ray *ray, int x);
const char	*c_fetch_texture_col(const t_img *texture, float texture_x);

// textures_2.c
void		draw_textures_wall_line(t_game *g, t_tex_line *texture, int frame_x,
				int height);

// utils.c
void		my_mlx_pixel_put(struct s_mlx_img *img, int x, int y, int color);
void		c_draw_line(struct s_mlx_img *img, t_pnt a, t_pnt b, int color);
char		*c_get_target_addr(t_img *i, int x, int y);
const char	*c_get_const_target_addr(const t_img *i, int x, int y);
void		c_draw_square(t_img *img, t_ipair coord, t_ipair colors, int size);
void		c_draw_square_2(t_img *img, t_ipair coord, uint64_t col, int size);

// ========================================================================== //
//                                 RAYCASTING                                 //
// ========================================================================== //

void		c_ray_calc_step_and_len(t_ray *ray, float pos_x, float pos_y);
void		c_ray_raycasting_loop(t_game *g, t_ray *ray);

// ========================================================================== //
//                                    MATHS                                   //
// ========================================================================== //

float		c_math_get_dist(float x1, float x2, float y1, float y2);
float		c_math_get_sq_dist(float x1, float x2, float y1, float y2);
void		c_math_rotate_vector(float *x, float *y, float angle);
int			c_min(int a, int b);
int			c_max(int a, int b);

#endif
