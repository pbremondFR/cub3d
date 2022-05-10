/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:56:50 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/11 00:39:06 by pbremond         ###   ########.fr       */
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

	i = 0;
	while (i < WIN_WIDTH)
	{
		ray.map_x = (int)g->x;
		ray.map_y = (int)g->y;
		ray_vec_adj = ((2 * i) / WIN_FWIDTH) - 1;
		ray.dir_x = g->dx + (g->cx * ray_vec_adj);
		ray.dir_y = g->dy + (g->cy * ray_vec_adj);
		ray.delta_dist_x = fabsf(1 / ray.dir_x);
		ray.delta_dist_y = fabsf(1 / ray.dir_y);
		c_ray_calc_step_and_len(&ray, g->x, g->y);
		c_ray_raycasting_loop(g, &ray);
		if (ray.side == 0)
			ray.c_plane_len = (ray.len_x - ray.delta_dist_x);
		else
			ray.c_plane_len = (ray.len_y - ray.delta_dist_y);
		ray_len_buf[i] = ray.c_plane_len;
		c_start_draw_wall(g, &ray, i++);
	}
}

void	c_print_background(t_game *g)
{
	const int	buf_siz = g->f.h * (g->f.ls / 4);
	const int	halfway = buf_siz / 2;
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
	// Code to add an infobar at the bottom of the screen
	// while (i < WIN_HEIGHT * (g->f.ls / 4))
	// {
	// 	if (frame_buf[i] != 0x202020)
	// 		frame_buf[i] = 0x202020;
	// 	++i;
	// }
}

void	c_debug_print_coords(t_game *g)
{
	char	buffer[16];
	t_ipair	coord;

	snprintf(buffer, 16, "%.3f %.3f", g->x, g->y);
	coord.a = 0;
	coord.b = WIN_HEIGHT - g->olay.h - 20 - (g->c->font->c_h * 3);
	c_putstr_to_frame_sbox(g, coord, 0xffffff, buffer);
}

char	*_create_test_string(unsigned int n)
{
	char			*str;
	unsigned int	i;

	str = ft_strnew(n);
	i = 1;
	while (i < n)
	{
		str[i - 1] = i;
		++i;
	}
	return (str);
}

void	_debug_tests(t_game *g)
{
	t_list	*node;
	t_sprt	*sprt;
	t_uint	i;

	i = 0;
	node = g->sprts_lst;
	while (node)
	{
		sprt = node->content;
		printf("> %d: %.3f\n", i++, sprt->dist_sq);
		node = node->next;
	}
}

int	c_render(void *handle)
{
	t_game	*g;
	t_ipair	coord;
	float	ray_len_buf[WIN_WIDTH];

	g = (t_game *)handle;
	if (g->k == KEYS_ESC)
		c_exit_program(handle);
	c_print_background(g);
	c_move_player(g);
	if (g->m_cap)
		c_mouse_look(g);
	c_render_raycast_loop(g, ray_len_buf);
	c_render_sprites(g, g->sprts_lst, ray_len_buf);
	c_player_decel(&g->vx, &g->vy, &g->va, g->k);
	c_debug_print_coords(g);
	coord.a = WIN_WIDTH / 2 - (float)((9.0f / 2) * g->c->font->c_w);
	coord.b = 0;
	c_putstr_to_frame_dbox(g, coord, 0xa0a0a0, "Cub3D \x15");
	mlx_put_image_to_window(g->mlx, g->mw, g->f.i, 0, 0);
	c_minimap_render(g, 0, 0);
	mlx_put_image_to_window(g->mlx, g->mw, g->olay.i,
		20, WIN_HEIGHT - g->olay.h - 20);
	// if (g->c->sprt_src[0])
	// 	mlx_put_image_to_window(g->mlx, g->mw, g->c->sprt_src[0]->i, 0, 0);
	// _debug_tests(g);
	// mlx_put_image_to_window(g->mlx, g->mw, g->c->font->i, 0, 0);
	return (0);
}
