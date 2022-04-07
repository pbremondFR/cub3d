/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   something.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:56:50 by pbremond          #+#    #+#             */
/*   Updated: 2022/04/07 14:58:53 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

void	draw_player(struct s_mlx_img *img, int x, int y, int color)
{
	draw_square(img, x - PLY_HITBX_RAD, y - PLY_HITBX_RAD, color);
}

static void	_calc_step_sidedist(t_ray *ray, float pos_x, float pos_y)
{
	if (ray->dir_x < 0.0f)
	{
		ray->step_x = -1;
		ray->side_dist_x = (pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0f - pos_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0.0f)
	{
		ray->step_y = -1;
		ray->side_dist_y = (pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0f - pos_y) * ray->delta_dist_y;
	}
}

static void	_ray_step_loop(t_game *g, t_ray *ray)
{
	while (1)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (g->c->map[ray->map_y][ray->map_x] == '1')
			break ;
	}
}

static void	_draw_ray(t_game *g, int height, int x, int color)
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

void	c_raycast_loop(t_game *g)
{
	t_uint	i;
	t_ray	ray;
	float	cam_x;
	int		line_height;
	int		color;

	i = 0;
	while (i < WIN_WIDTH)
	{
		ray.map_x = (int)g->x;
		ray.map_y = (int)g->y;
		cam_x = 2 * i / (float)WIN_WIDTH - 1;
		ray.dir_x = g->dx + (g->px * cam_x);
		ray.dir_y = g->dy + (g->py * cam_x);
		ray.delta_dist_x = fabsf(1 / ray.dir_x);
		ray.delta_dist_y = fabsf(1 / ray.dir_y);
		_calc_step_sidedist(&ray, g->x, g->y);
		_ray_step_loop(g, &ray);
		if (ray.side == 0)
			ray.len = (ray.side_dist_x - ray.delta_dist_x);
		else
			ray.len = (ray.side_dist_y - ray.delta_dist_y);
		line_height = (int)(WIN_HEIGHT / ray.len);
		color = 0xff0000;
		if (ray.side == 1)
			color = color >> 16;
		_draw_ray(g, line_height, i, color);
		++i;
	}
}

#ifndef MLX_BETA

int	c_render(void *handle)
{
	t_game	*g;

	g = (t_game *)handle;
	printf("Player: %f\t%f\n", g->x, g->y);
	printf("Accel:  %f\t%f\n", g->vx, g->vy);
	g->x += g->vx;
	g->y -= g->vy;
	if (g->vx > 0.0f)
		g->vx -= fminf(DECEL, g->vx);
	else if (g->vx < 0.0f)
		g->vx -= fmaxf(-DECEL, g->vx);
	if (g->vy > 0.0f)
		g->vy -= fminf(DECEL, g->vy);
	else if (g->vy < 0.0f)
		g->vy -= fmaxf(-DECEL, g->vy);
	mlx_pixel_put(g->mlx, g->mw, nearbyintf(g->x), nearbyintf(g->y), 0xffffff);
	usleep(10000);
	return (0);
}

#else

// void	c_reset_image(t_img *img, int color)
// {
// 	int	i;

// 	(void)color;
// 	i = 0;
// 	while (i < WIN_HEIGHT * WIN_WIDTH * img->bpp)
// 	{
// 		img->addr[i++] = '\0';
// 	}
// }

int	c_render(void *handle)
{
	t_game	*g;

	g = (t_game *)handle;
	printf("Player: %d\t%d\n", (int)g->x, (int)g->y);
	// printf("Accel:  %f\t%f\n", g->vx, g->vy);
	printf("Player dx: %.3f\tdy: %.3f\n", g->dx, g->dy);
	printf("Player px: %.3f\tpy: %.3f\n", g->px, g->py);
	// draw_player(&g->i, g->x * MAP_TILE_SIZE, g->y * MAP_TILE_SIZE, 0x00);
	// c_draw_vision(g, MAP_TILE_SIZE, 0x00, 0x00);
	// c_reset_image(&g->i, 0x00);
	mlx_destroy_image(g->mlx, g->i.i);
	g->i.i = mlx_new_image(g->mlx, WIN_WIDTH, WIN_HEIGHT);
	g->i.addr = mlx_get_data_addr(g->i.i, &g->i.bpp, &g->i.ls, &g->i.e);
	c_move_player(g);
	c_raycast_loop(g);
	// draw_player(&g->i, g->x * MAP_TILE_SIZE, g->y * MAP_TILE_SIZE, 0x7f7fff);
	// c_draw_vision(g, MAP_TILE_SIZE, 0xff0000, 0x00ff00);
	c_player_decel(&g->vx, &g->vy, g->k);
	mlx_put_image_to_window(g->mlx, g->mw, g->i.i, 0, 0);
	mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, g->mw);
	return (0);
}

#endif
