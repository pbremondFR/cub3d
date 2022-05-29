/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:56:50 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/29 08:22:26 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d_bonus.h>

// void	_draw_wall_from_ray(t_game *g, int height, int x, int color)
// {
// 	t_pnt	a;
// 	t_pnt	b;
// 	int		i;

// 	a.x = x;
// 	b.x = x;
// 	a.y = (-height / 2) + (WIN_HEIGHT / 2);
// 	if (a.y < 0)
// 		a.y = 0;
// 	b.y = (height / 2) + (WIN_HEIGHT / 2);
// 	if (b.y > WIN_HEIGHT - 1)
// 		b.y = WIN_HEIGHT - 1;
// 	i = a.y;
// 	while (i < b.y)
// 	{
// 		my_mlx_pixel_put(&g->f, x, i, color);
// 		++i;
// 	}
// }

void	c_render_raycast_loop(t_game *g, float ray_len_buf[])
{
	t_uint	i;
	t_ray	ray;
	float	ray_vec_adj;
	int8_t	tex_offset;

	i = 0;
	while (i < WIN_WIDTH)
	{
		tex_offset = 0;
		ray.map_x = (int)g->x;
		ray.map_y = (int)g->y;
		ray_vec_adj = ((2 * i) / WIN_FWIDTH) - 1;
		ray.dir_x = g->dx + (g->cx * ray_vec_adj);
		ray.dir_y = g->dy + (g->cy * ray_vec_adj);
		ray.delta_dist_x = fabsf(1 / ray.dir_x);
		ray.delta_dist_y = fabsf(1 / ray.dir_y);
		c_ray_calc_step_and_len(&ray, g->x, g->y);
		c_ray_raycasting_loop_bonus(g, &ray, &tex_offset);
		if (ray.side == RAY_HIT_X)
			ray.c_plane_len = (ray.len_x - ray.delta_dist_x);
		else
			ray.c_plane_len = (ray.len_y - ray.delta_dist_y);
		ray_len_buf[i] = ray.c_plane_len;
		c_start_draw_wall(g, &ray, i++, tex_offset);
	}
}

void	c_print_background(t_game *g)
{
	const int	buf_siz = g->f.h * (g->f.ls >> 2);
	const int	halfway = buf_siz >> 1;
	int			*frame_buf;
	int			i;

	frame_buf = (int *)g->f.addr;
	i = 0;
	while (i < buf_siz)
	{
		if (i < halfway && frame_buf[i] != g->c->c)
			frame_buf[i] = g->c->c;
		else if (i >= halfway && frame_buf[i] != g->c->f)
			frame_buf[i] = g->c->f;
		++i;
	}
}

static void	_title_overlay(t_game *g, const char *str, t_uint color)
{
	const float		box_len = (float)ft_strlen(str) + 2;
	const int		char_w = g->c->font->c_w;
	const t_ipair	coords = {(WIN_WIDTH / 2) - ((box_len / 2) * char_w),
		0};

	c_putstr_to_frame_dbox(g, coords, color, str);
}

void	c_print_player_coords(t_game *g)
{
	char			buffer[16];
	const t_ipair	coord = {0,
		(WIN_HEIGHT - g->olay.h - 20 - (g->c->font->c_h * 3))};

	snprintf(buffer, 16, "%.3f %.3f", g->x, g->y);
	c_putstr_to_frame_sbox(g, coord, 0xffffff, buffer);
}

// void	debug_tests(t_game *g)
// {
// 	unsigned int	i;

// 	// for (i = (int)(sizeof(g->k) * 8) - 1; i >= 0; --i)
// 	// {
// 	// 	if (i % 8 == 7 && i != 15)
// 	// 		ft_putchar(' ');
// 	// 	if ((g->k >> i) & 1)
// 	// 		ft_putchar('1');
// 	// 	else
// 	// 		ft_putchar('0');
// 	// }
// 	// ft_putchar('\n');
// 	for (i = 0; i < g->c->n_doors; ++i)
// 	{
// 		const t_door	*door;
// 		door = &g->c->doors[i];
// 		printf("door %d at %d;%d: %d\n", i, door->x, door->y, door->state);
// 	}
// }

// Main rendering loop
int	c_render(void *handle)
{
	t_game	*g;
	float	ray_len_buf[WIN_WIDTH];

	g = (t_game *)handle;
	clock_gettime(CLOCK_MONOTONIC, &g->t);
	if (g->k == KEYS_ESC)
		c_exit_program(g, 0);
	c_print_background(g);
	c_move_player(g);
	if (g->m_cap)
		c_mouse_look(g);
	if (g->k & KEYS_M1)
		c_player_try_open_door(g, g->c->doors, g->c->n_doors);
	c_render_raycast_loop(g, ray_len_buf);
	c_doors_routine(&g->t, g->c->doors, g->c->n_doors);
	c_render_sprites(g, g->sprts_lst, ray_len_buf);
	c_print_player_coords(g);
	_title_overlay(g, "Cub3D \x15", 0xa0a0a0);
	mlx_put_image_to_window(g->mlx, g->mw, g->f.i, 0, 0);
	c_minimap_render(g, MINIMAP_BORDER_SIZE, MINIMAP_BORDER_SIZE);
	mlx_put_image_to_window(g->mlx, g->mw, g->olay.i,
		20, WIN_HEIGHT - g->olay.h - 20);
	c_player_decel(&g->vx, &g->vy, &g->va, g->k);
	return (0);
}
