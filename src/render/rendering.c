/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:56:50 by pbremond          #+#    #+#             */
/*   Updated: 2022/04/21 12:02:27 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

static void	_draw_wall_from_ray(t_game *g, int height, int x, int color)
{
	t_pnt	a;
	t_pnt	b;
	int		i;

	a.x = x;
	b.x = x;
	a.y = (-height / 2) + (WIN_HEIGHT / 2);
	if (a.y < 0)
		a.y = 0;
	b.y = (height / 2) + (WIN_HEIGHT / 2);
	if (b.y > WIN_HEIGHT)
		b.y = WIN_HEIGHT - 1;
	i = a.y;
	while (i < b.y)
	{
		my_mlx_pixel_put(&g->i, x, i, color);
		++i;
	}
}

void	c_render_raycast_loop(t_game *g)
{
	t_uint	i;
	t_ray	ray;
	float	ray_vec_adj;
	int		line_height;
	int		color;

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
		color = 0xff0000;
		if (ray.side == 1)
			color = color >> 16;
		_draw_wall_from_ray(g, line_height, i++, color);
	}
}

int	c_render(void *handle)
{
	t_game	*g;

	g = (t_game *)handle;
	printf("Player: %.3f\t%.3f\n", g->x, g->y);
	// printf("Accel:  %f\t%f\n", g->vx, g->vy);
	// printf("Player dx: %.3f\tdy: %.3f\n", g->dx, g->dy);
	// printf("Player cx: %.3f\tcy: %.3f\n", g->cx, g->cy);
	// draw_player(&g->i, g->x * MAP_TILE_SIZE, g->y * MAP_TILE_SIZE, 0x00);
	// c_draw_vision(g, MAP_TILE_SIZE, 0x00, 0x00);
	mlx_destroy_image(g->mlx, g->i.i);
	g->i.i = mlx_new_image(g->mlx, WIN_WIDTH, WIN_HEIGHT);
	g->i.addr = mlx_get_data_addr(g->i.i, &g->i.bpp, &g->i.ls, &g->i.e);
	c_move_player(g);
	c_render_raycast_loop(g);
	// draw_player(&g->i, g->x * MAP_TILE_SIZE, g->y * MAP_TILE_SIZE, 0x7f7fff);
	// c_draw_vision(g, MAP_TILE_SIZE, 0xff0000, 0x00ff00);
	c_player_decel(&g->vx, &g->vy, &g->va, g->k);
	mlx_put_image_to_window(g->mlx, g->mw, g->i.i, 0, 0);
	mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, g->mw);
	return (0);
}
