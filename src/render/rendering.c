/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:56:50 by pbremond          #+#    #+#             */
/*   Updated: 2022/04/22 14:41:12 by pbremond         ###   ########.fr       */
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
	if (b.y > WIN_HEIGHT - 1)
		b.y = WIN_HEIGHT - 1;
	i = a.y;
	while (i < b.y)
	{
		my_mlx_pixel_put(&g->f, x, i, color);
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

void	_test_display_cache(t_game *g, t_img *img, int x, int y)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	while (i < img->w)
	{
		j = 0;
		while (j < img->h)
		{
			color = *(int *)(img->addr + (i * img->ls + j * (img->bpp / 8)));
			my_mlx_pixel_put(&g->f, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	c_print_coords(t_game *g)
{
	char	buffer[16];

	snprintf(buffer, 16, "%.3f %.3f", g->x, g->y);
	mlx_string_put(g->mlx, g->mw, 10, 20, 0xffffff, buffer);
}

int	c_render(void *handle)
{
	t_game	*g;

	g = (t_game *)handle;
	mlx_destroy_image(g->mlx, g->f.i);
	g->f.i = mlx_new_image(g->mlx, WIN_WIDTH, WIN_HEIGHT);
	g->f.addr = mlx_get_data_addr(g->f.i, &g->f.bpp, &g->f.ls, &g->f.e);
	c_move_player(g);
	c_render_raycast_loop(g);
	c_player_decel(&g->vx, &g->vy, &g->va, g->k);
	// _test_display_cache(g, g->c->n, 50, 50);
	mlx_put_image_to_window(g->mlx, g->mw, g->f.i, 0, 0);
	// mlx_put_image_to_window(g->mlx, g->mw, g->c->n->i, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	c_print_coords(g);
	mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, g->mw);
	return (0);
}
