/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:56:50 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/29 03:59:04 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

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

void	c_render_raycast_loop(t_game *g)
{
	t_uint	i;
	t_ray	ray;
	float	ray_vec_adj;
	int		line_height;

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
		line_height = (int)(WIN_HEIGHT / ray.c_plane_len);
		c_start_draw_wall(g, &ray, i++, 0);
	}
}

void	c_print_background(t_game *g)
{
	const int	buf_siz = g->f.h * (g->f.ls / 4);
	int			*frame_buf;
	int			i;

	frame_buf = (int *)g->f.addr;
	i = 0;
	while (i < buf_siz / 2)
		frame_buf[i++] = g->c->c;
	while (i < buf_siz)
		frame_buf[i++] = g->c->f;
}

int	c_render(void *handle)
{
	t_game	*g;

	g = (t_game *)handle;
	if (g->k == KEYS_ESC)
		c_exit_program(g, 0);
	c_print_background(g);
	c_move_player(g);
	if (g->m_cap)
		c_mouse_look(g);
	c_render_raycast_loop(g);
	c_player_decel(&g->vx, &g->vy, &g->va, g->k);
	mlx_put_image_to_window(g->mlx, g->mw, g->f.i, 0, 0);
	return (0);
}
