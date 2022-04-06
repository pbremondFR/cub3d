/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:56:50 by pbremond          #+#    #+#             */
/*   Updated: 2022/04/06 15:53:20 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

void	_collision_handler(t_game *g, float acc_x, float acc_y)
{
	if (acc_x < 0.0f)
	{
		if (g->x + g->vx + acc_x < 0.0f)
			g->vx = -g->x;
	}
	else if (acc_x > 0.0f)
	{
		if (g->x + g->vx + 50.0f + acc_x > WIN_FWIDTH)
			g->vx = WIN_FWIDTH - g->x;
	}
	if (acc_y < 0.0f)
	{
		if (g->y + g->vy + acc_y < 0.0f)
			g->vy = -g->y;
	}
	else if (acc_y > 0.0f)
	{
		if (g->y + g->vy + 50.0f + acc_y > WIN_FHEIGHT)
			g->vy = WIN_FHEIGHT - g->y;
	}
}

// TODO: Make a proper exit function
void	c_move_player(t_game *g)
{
	float	acc_x;
	float	acc_y;

	acc_x = g->vx;
	acc_y = g->vy;
	if (g->k & KEYS_W)
		acc_y += ACCEL;
	if (g->k & KEYS_S)
		acc_y -= ACCEL;
	if (g->k & KEYS_D)
		acc_x += ACCEL;
	if (g->k & KEYS_A)
		acc_x -= ACCEL;
	if (g->k & KEYS_ESC)
		exit(0);
	g->vx += acc_x;
	g->vy += acc_y;
	// _collision_handler(g, acc_x, acc_y);
	g->x += g->vx;
	g->y -= g->vy;
}

// Imma steal that for now
void	my_mlx_pixel_put(struct s_mlx_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->ls + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_square(struct s_mlx_img *img, int x, int y, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 50)
	{
		j = -1;
		while (++j < 50)
			my_mlx_pixel_put(img, x + j, y + i, color);
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

 int	_stupid_boudary_check(float pos, float velocity, float limit)
{
	if (pos + velocity < 0.0f || pos + 50 + velocity > limit)
		return (0);
	return (1);
}

int	c_render(void *handle)
{
	t_game	*g;

	g = (t_game *)handle;
	printf("Player: %f\t%f\n", g->x, g->y);
	printf("Accel:  %f\t%f\n", g->vx, g->vy);
	draw_square(&g->i, g->x, g->y, 0x0);
	c_move_player(g);
	g->x += g->vx;
	g->y -= g->vy;
	draw_square(&g->i, g->x, g->y, 0xffffff);
	if (g->vx > 0.0f)
		g->vx -= fminf(DECEL, g->vx);
	else if (g->vx < 0.0f)
		g->vx -= fmaxf(-DECEL, g->vx);
	if (g->vy > 0.0f)
		g->vy -= fminf(DECEL, g->vy);
	else if (g->vy < 0.0f)
		g->vy -= fmaxf(-DECEL, g->vy);
	mlx_put_image_to_window(g->mlx, g->mw, g->i.i, 0, 0);
	mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, g->mw);
	usleep(10000);
	return (0);
}

#endif
