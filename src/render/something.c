/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   something.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:56:50 by pbremond          #+#    #+#             */
/*   Updated: 2022/04/06 16:43:15 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

// TODO: Make a proper exit function
void	c_move_player(t_game *g)
{
	if (g->k & KEYS_W && g->vy < MAX_VEL)
		g->vy += ACCEL;
	if (g->k & KEYS_S && g->vy > -MAX_VEL)
		g->vy -= ACCEL;
	if (g->k & KEYS_D && g->vx < MAX_VEL)
		g->vx += ACCEL;
	if (g->k & KEYS_A && g->vx > -MAX_VEL)
		g->vx -= ACCEL;
	if (g->k & KEYS_ESC)
		exit(0);
	g->x += g->vx;
	g->y -= g->vy;
	if (g->x + PLY_HITBX_RAD > WIN_FWIDTH)
		g->x = WIN_FWIDTH - PLY_HITBX_RAD;
	else if (g->x - PLY_HITBX_RAD < 0.0f)
		g->x = 0.0f + PLY_HITBX_RAD;
	if (g->y + PLY_HITBX_RAD > WIN_FHEIGHT)
		g->y = WIN_FHEIGHT - PLY_HITBX_RAD;
	else if (g->y - PLY_HITBX_RAD < 0.0f)
		g->y = 0.0f + PLY_HITBX_RAD;
}

void	draw_player(struct s_mlx_img *img, int x, int y, int color)
{
	draw_square(img, x - PLY_HITBX_RAD, y - PLY_HITBX_RAD, color);
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

int	c_render(void *handle)
{
	t_game	*g;

	g = (t_game *)handle;
	printf("Player: %f\t%f\n", g->x, g->y);
	printf("Accel:  %f\t%f\n", g->vx, g->vy);
	draw_player(&g->i, g->x, g->y, 0x0);
	c_move_player(g);
	draw_player(&g->i, g->x, g->y, 0xffffff);
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
	return (0);
}

#endif
